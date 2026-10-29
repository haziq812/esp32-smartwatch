# ESP32 Smartwatch ⌚

A DIY smartwatch built from scratch on the **ESP32-S3**, made to learn embedded hardware and firmware and to be upgraded over time.

> Status: 🛒 **Parts sourcing / breadboard prototype**

## Features

| Feature | Status |
|---|---|
| Round 240×240 watch face (GC9A01) | 🚧 In progress |
| Time sync over WiFi (NTP) | 🚧 In progress |
| Accelerometer readout (MPU6050) | 🚧 In progress |
| Touch input (CST816) | ⏳ Planned |
| Step counter | ⏳ Planned |
| Wrist-raise to wake + deep sleep | ⏳ Planned |
| Battery level | ⏳ Planned |
| Vibration alerts | ⏳ Planned |
| Phone notifications over BLE | ⏳ Planned |
| Heart rate / SpO2 (MAX30102) | 💡 Upgrade |
| 3D-printed case | 💡 Upgrade |

## Hardware

Core parts: **Seeed XIAO ESP32S3**, **1.28" GC9A01 round LCD with CST816 touch**, **MPU6050 IMU**, and a **3.7 V 300 mAh LiPo**.

- 🧾 Full parts list (with Shopee Malaysia search terms): [`docs/parts-list.md`](docs/parts-list.md)
- 🔌 Wiring and pin map: [`docs/wiring.md`](docs/wiring.md)

## Firmware

Built with [PlatformIO](https://platformio.org/) (Arduino framework).

```bash
cd firmware
cp include/config.example.h include/config.h   # then add your WiFi details
pio run -t upload
pio device monitor
```

`include/config.h` is git-ignored, so your WiFi password never gets committed.

### Layout

```
firmware/
├── platformio.ini        # board + libraries
├── include/
│   ├── pins.h            # every GPIO in one place
│   └── config.example.h  # WiFi / timezone template
└── src/
    └── main.cpp          # watch face, NTP, IMU
```

## Roadmap

The full phased plan with checklists is in [**ROADMAP.md**](ROADMAP.md).

| Phase | Focus |
|---|---|
| 0 | Setup and parts |
| 1 | Breadboard bring-up |
| 2 | Watch firmware core (UI, touch, settings) |
| 3 | Smart features (steps, wrist-raise, vibration) |
| 4 | Power and battery life |
| 5 | Phone connection over BLE |
| 6 | Hardware build and case |
| 7 | Upgrades (heart rate, GPS, custom PCB) |

## Safety notes

- ⚠️ **Check LiPo polarity with a multimeter before plugging in.** Cheap batteries often have swapped wires.
- Never short, puncture, or overcharge a LiPo, and don't leave it charging unattended.

## License

MIT
