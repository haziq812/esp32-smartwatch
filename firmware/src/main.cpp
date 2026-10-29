// ESP32 Smartwatch: first prototype firmware
// Shows the time (synced over WiFi/NTP) and live accelerometer data
// on a GC9A01 round display.

#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <time.h>
#include <Arduino_GFX_Library.h>
#include <Adafruit_MPU6050.h>

#include "pins.h"
#if __has_include("config.h")
#include "config.h"
#else
#warning "config.h not found, using config.example.h. Copy it and add your WiFi details."
#include "config.example.h"
#endif

// ---------- Display ----------
Arduino_DataBus *bus = new Arduino_ESP32SPI(
    PIN_TFT_DC, PIN_TFT_CS, PIN_TFT_SCK, PIN_TFT_MOSI, GFX_NOT_DEFINED);
Arduino_GFX *gfx = new Arduino_GC9A01(bus, PIN_TFT_RST, 0 /* rotation */, true /* IPS */);

// ---------- Sensors ----------
Adafruit_MPU6050 mpu;
bool imuOk = false;

// ---------- Colors (RGB565) ----------
const uint16_t COL_BG     = 0x0000;  // black
const uint16_t COL_TIME   = 0xFFFF;  // white
const uint16_t COL_DATE   = 0x07FF;  // cyan
const uint16_t COL_DIM    = 0x7BEF;  // grey
const uint16_t COL_ACCENT = 0xFD20;  // orange

void drawCentered(const char *text, int16_t y, uint8_t size, uint16_t color) {
  gfx->setTextSize(size);
  gfx->setTextColor(color, COL_BG);  // background color overwrites old text, no flicker
  int16_t x1, y1;
  uint16_t w, h;
  gfx->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  gfx->setCursor((240 - w) / 2, y);
  gfx->print(text);
}

void connectWiFiAndSyncTime() {
  drawCentered("Connecting WiFi", 110, 2, COL_DIM);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    delay(250);
  }

  gfx->fillScreen(COL_BG);
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi failed, time will not be synced");
    return;
  }

  configTzTime(TZ_INFO, NTP_SERVER);
  struct tm t;
  if (getLocalTime(&t, 10000)) {
    Serial.println("Time synced");
  }

  // Time is kept by the ESP32's internal clock after sync,
  // so WiFi can be turned off to save battery.
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void drawWatchFace() {
  static int lastSecond = -1;
  struct tm t;
  if (!getLocalTime(&t, 0)) {
    drawCentered("--:--", 85, 6, COL_TIME);
    return;
  }
  if (t.tm_sec == lastSecond) return;
  lastSecond = t.tm_sec;

  char buf[32];
  strftime(buf, sizeof(buf), "%H:%M", &t);
  drawCentered(buf, 80, 6, COL_TIME);

  snprintf(buf, sizeof(buf), "%02d", t.tm_sec);
  drawCentered(buf, 135, 2, COL_ACCENT);

  strftime(buf, sizeof(buf), "%a %d %b", &t);
  drawCentered(buf, 50, 2, COL_DATE);
}

void drawImu() {
  static uint32_t lastDraw = 0;
  if (!imuOk || millis() - lastDraw < 200) return;
  lastDraw = millis();

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  char buf[32];
  snprintf(buf, sizeof(buf), "%+5.1f %+5.1f %+5.1f",
           a.acceleration.x, a.acceleration.y, a.acceleration.z);
  drawCentered(buf, 170, 1, COL_DIM);
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_TFT_BL, OUTPUT);
  digitalWrite(PIN_TFT_BL, HIGH);
  pinMode(PIN_VIBRATE, OUTPUT);
  digitalWrite(PIN_VIBRATE, LOW);

  gfx->begin();
  gfx->fillScreen(COL_BG);

  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  imuOk = mpu.begin(0x68, &Wire);
  if (imuOk) {
    mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  } else {
    Serial.println("MPU6050 not found, check wiring");
  }

  connectWiFiAndSyncTime();
}

void loop() {
  drawWatchFace();
  drawImu();
  delay(20);
}
