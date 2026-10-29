# Wiring

All pins are defined in [`firmware/include/pins.h`](../firmware/include/pins.h). If you change wiring, change it there.

## Pin map: XIAO ESP32S3

| XIAO pin | GPIO | Connects to |
|---|---|---|
| D0 | 1 | Battery voltage divider (ADC) |
| D1 | 2 | LCD `RST` + touch `RST` |
| D2 | 3 | LCD `CS` |
| D3 | 4 | LCD `DC` |
| D4 | 5 | I²C `SDA` (touch + MPU6050) |
| D5 | 6 | I²C `SCL` (touch + MPU6050) |
| D6 | 43 | LCD `BL` (backlight) |
| D7 | 44 | Touch `INT` |
| D8 | 7 | LCD `SCL`/`SCK` (SPI clock) |
| D9 | 8 | Vibration motor (via transistor) |
| D10 | 9 | LCD `SDA`/`MOSI` (SPI data) |
| 3V3 | – | LCD `VCC`, MPU6050 `VCC` |
| GND | – | All `GND` |
| BAT+ / BAT− (pads underneath) | – | LiPo, via the slide switch on `+` |

> Display boards label SPI data as `SDA` and clock as `SCL`. On the display, those are **SPI**, not I²C.

## Shared I²C bus

The touch controller (CST816, address `0x15`) and MPU6050 (address `0x68`) share SDA/SCL. Most breakout boards already have pull-up resistors.

## Battery voltage sense

```
BAT+ ──[200k]──┬──[200k]── GND
               │
               D0 (GPIO1)
```

The divider halves the battery voltage (4.2 V max becomes 2.1 V) so it stays within the ADC range.

## Vibration motor

```
D9 ──[1k]── B (2N2222)
            C ── motor (−)      motor (+) ── 3V3
            E ── GND
1N4148 across the motor (stripe toward 3V3)
```

The ESP32 pin can't power a motor directly, so the transistor acts as a switch, and the diode protects against voltage spikes from the motor.

## Before powering on

1. Check for shorts between 3V3 and GND with a multimeter.
2. Check LiPo polarity against the BAT+ / BAT− pads.
3. For the first upload, power over USB only, with no battery connected.
