#pragma once

// Pin map for Seeed XIAO ESP32S3. See docs/wiring.md.

// Display (GC9A01, SPI)
#define PIN_TFT_SCK   7   // D8
#define PIN_TFT_MOSI  9   // D10
#define PIN_TFT_CS    3   // D2
#define PIN_TFT_DC    4   // D3
#define PIN_TFT_RST   2   // D1 (shared with touch reset)
#define PIN_TFT_BL    43  // D6

// I2C bus (CST816 touch + MPU6050)
#define PIN_I2C_SDA   5   // D4
#define PIN_I2C_SCL   6   // D5
#define PIN_TOUCH_INT 44  // D7

// Other
#define PIN_BAT_ADC   1   // D0, through a 1:2 voltage divider
#define PIN_VIBRATE   8   // D9, through an NPN transistor
