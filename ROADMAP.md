# Roadmap

The plan for taking this smartwatch from a pile of parts to a watch I actually wear, and then upgrading it.

Each phase has a **goal**, a **checklist**, a **definition of done**, and the things it should teach me. Tick the boxes as I go. Phases build on each other, but upgrades in Phase 7 can be picked in any order.

```
Phase 0  Setup & parts          ████ shopping + toolchain
Phase 1  Breadboard bring-up    ████ every part works on its own
Phase 2  Watch firmware core    ████ time, UI, touch
Phase 3  Smart features         ████ steps, wake, vibration
Phase 4  Power & battery        ████ runs all day on battery
Phase 5  Phone connection       ████ BLE notifications
Phase 6  Hardware build         ████ soldered + cased, wearable
Phase 7  Upgrades               ████ heart rate, GPS, sound, PCB
```

---

## Phase 0: Setup and parts

**Goal:** have every part and tool on the desk, and a working toolchain.

- [ ] Order the core parts from Shopee (see [`docs/parts-list.md`](docs/parts-list.md))
- [ ] Order tools: soldering iron, solder, flux, multimeter, breadboard, jumpers
- [ ] Install VS Code and the PlatformIO extension
- [ ] Flash a "blink" sketch to the XIAO ESP32S3 to prove upload works
- [ ] Open the serial monitor and print "hello" from the board
- [ ] Solder header pins onto the XIAO, display, and MPU6050

**Done when:** the board blinks and prints to the serial monitor.

**Learn:** PlatformIO project layout, uploading firmware, the serial monitor, basic soldering.

---

## Phase 1: Breadboard bring-up

**Goal:** prove every part works on its own before combining them.

- [ ] Wire the GC9A01 display on SPI, then draw shapes and text
- [ ] Get the backlight pin working (on/off, then PWM dimming)
- [ ] Wire the MPU6050 on I²C, then print accelerometer values over serial
- [ ] Run an I²C scanner and confirm `0x68` (MPU6050) and `0x15` (touch)
- [ ] Read the CST816 touch: print X/Y coordinates and gestures
- [ ] Wire the vibration motor via the transistor and pulse it
- [ ] Flash `firmware/` and see the time + accelerometer on screen

**Done when:** display, IMU, touch and motor all work together on the breadboard.

**Learn:** SPI vs I²C, pull-up resistors, reading datasheets, using a transistor as a switch.

---

## Phase 2: Watch firmware core

**Goal:** a usable watch UI on the breadboard.

- [ ] Restructure firmware into modules (`display`, `clock`, `imu`, `touch`, `ui`)
- [ ] Sync time over WiFi (NTP), then turn WiFi off
- [ ] Draw an analog watch face (hands, ticks) as well as the digital one
- [ ] Use an off-screen buffer (canvas) for flicker-free drawing
- [ ] Add [LVGL](https://lvgl.io/) for proper UI widgets and screens
- [ ] Swipe between screens: watch face, steps, settings
- [ ] Settings screen: brightness, 12/24h, re-sync time
- [ ] Save settings to flash (`Preferences` library)

**Done when:** I can swipe through screens and settings survive a reboot.

**Learn:** firmware architecture, UI frameworks on microcontrollers, non-volatile storage.

---

## Phase 3: Smart features

**Goal:** the watch does useful things on its own.

- [ ] Step counter from accelerometer data (peak detection + filtering)
- [ ] Daily step total that resets at midnight
- [ ] Wrist-raise detection, so the screen turns on when I look at it
- [ ] Screen timeout: dim, then turn off after a few seconds
- [ ] Vibration patterns (short tap, double tap, long buzz)
- [ ] Stopwatch and countdown timer apps
- [ ] Alarm with vibration

**Done when:** I can wear the breadboard version (carefully!) and steps and wake work reliably.

**Learn:** signal processing basics, state machines, interrupts.

---

## Phase 4: Power and battery

**Goal:** the watch lasts at least a full day on a 300 mAh battery.

- [ ] Connect the LiPo through the slide switch (**check polarity first!**)
- [ ] Battery voltage reading via the divider on D0
- [ ] Battery percentage + charging indicator on screen
- [ ] Measure current draw with a multimeter: screen on, screen off, sleep
- [ ] Light sleep when the screen is off
- [ ] Deep sleep with wake on touch interrupt or IMU motion interrupt
- [ ] Lower CPU frequency when idle
- [ ] Log battery life in [`docs/power-log.md`](docs/power-log.md) after each improvement

**Targets:**

| State | Target current |
|---|---|
| Screen on | < 50 mA |
| Screen off, idle | < 5 mA |
| Deep sleep | < 1 mA |

**Done when:** it runs from morning to night on one charge.

**Learn:** ESP32 sleep modes, power budgeting, wake sources, LiPo safety.

---

## Phase 5: Phone connection (BLE)

**Goal:** see phone notifications on the watch.

- [ ] BLE advertising and connecting from a phone (test with nRF Connect)
- [ ] Custom BLE service: set time, read battery, read steps
- [ ] Notifications from Android via [Gadgetbridge](https://gadgetbridge.org/) or a small companion app
- [ ] Show notification popups with vibration
- [ ] "Find my phone" button
- [ ] Music controls (play/pause, next)
- [ ] Over-the-air (OTA) firmware updates over WiFi

**Done when:** a WhatsApp message on my phone buzzes the watch.

**Learn:** BLE services and characteristics, GATT, mobile ↔ device protocols, OTA.

---

## Phase 6: Hardware build

**Goal:** a wearable watch, not a breadboard.

- [ ] Plan the layout: stack display, board, battery, and sensors
- [ ] Solder everything with 30 AWG wire, keeping it short and neat
- [ ] Insulate with Kapton tape
- [ ] Design a case in Fusion 360 / FreeCAD / Tinkercad
- [ ] 3D print the case (own printer or a print service)
- [ ] Fit a 20 mm or 22 mm watch strap
- [ ] Add a physical button (wake / back)
- [ ] Commit case files to `hardware/case/`

**Done when:** I wear it for a full day.

**Learn:** compact soldering, CAD, 3D printing, mechanical design.

---

## Phase 7: Upgrades

Pick these in any order once the base watch works.

### Health
- [ ] MAX30102 heart rate + SpO2
- [ ] Sleep tracking from IMU movement
- [ ] Weekly step and heart-rate history graphs

### Sensors and features
- [ ] DS3231 RTC for accurate offline time
- [ ] GPS (ATGM336H) for run tracking
- [ ] Speaker (MAX98357A) for alarm sounds
- [ ] Microphone for voice notes or commands
- [ ] Compass / altimeter (e.g. BMP280)

### Software
- [ ] Custom watch face designer (upload faces from the phone)
- [ ] Weather from an API (synced over WiFi)
- [ ] Homelab / server status widget (ping my home server)
- [ ] Mini games

### Hardware v2
- [ ] Design a custom PCB in KiCad
- [ ] Order PCBs from JLCPCB / PCBWay
- [ ] Thinner case for the custom PCB
- [ ] Wireless charging

---

## Progress log

| Date | Milestone |
|---|---|
| 2026-10-30 | Repo created, parts list, wiring plan, first firmware draft |
