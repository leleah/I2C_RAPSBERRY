<!-- PROJECT HEADER -->
<h1 align="center">?? LM75 Temperature Sensor via I?C on Raspberry Pi</h1>

<p align="center">
  <b>Read temperature data from the LM75 digital sensor via the I?C interface using C on Raspberry Pi</b><br>
  <sub>Created by <b>Leah</b> — Radio Electronics Engineer</sub>
</p>

---

## ?? About the Project

This project demonstrates direct communication with an **LM75** temperature sensor using the **I?C bus** on a **Raspberry Pi 4B**.  
All interaction is done at the low-level via the Linux `/dev/i2c-*` interface, without external libraries.

It’s a minimal example for learning embedded Linux I?C programming in C.

---

## ?? Hardware Setup

- **Board:** Raspberry Pi 4 Model B  
- **Sensor:** LM75 (Texas Instruments or compatible)  
- **Interface:** I?C bus (`/dev/i2c-1`)  
- **Power:** 3.3 V  
- **Pull-ups:** Built-in 4.7 k? on SDA/SCL (no external needed)

### ?? Pinout

| LM75 Pin | Raspberry Pi Pin | Description |
|-----------|------------------|--------------|
| VCC | 3.3 V (Pin 1) | Power supply |
| GND | GND (Pin 6) | Ground |
| SDA | GPIO 2 / SDA (Pin 3) | I?C data |
| SCL | GPIO 3 / SCL (Pin 5) | I?C clock |
| A0–A2 | GND | Address bits (`0x48`–`0x4F`) |

> In this setup, the sensor address is `0x60`.

---

## ?? Software Setup

### 1?? Enable I?C on Raspberry Pi
```bash
sudo raspi-config
# Interface Options > I2C > Enable
sudo reboot
2?? Verify Device Connection
sudo apt install i2c-tools
i2cdetect -y 1

? Expected result: address 60 visible in the scan table.
?? Build & Run

gcc lm75_read.c -o lm75_read
sudo ./lm75_read

?? Example output:

Connected to LM75 (0x60)
Temperature: 24.5 °C

?? Code Overview

Main sequence:

    Open /dev/i2c-1

    Select device address (0x60)

    Write 0x00 > temperature register

    Read 2 bytes of raw data

    Convert 9-bit signed value > Celsius (temp_raw * 0.5)

?? File Structure

.
+-- lm75_read.c      # Source code
L-- README.md        # Documentation

?? Gallery / Demo
<p align="center"> <!-- Add screenshots or photos --> <img src="images/lm75_setup.jpg" width="400" alt="LM75 on breadboard"> <br> <sub>LM75 sensor connected to Raspberry Pi</sub> </p> <p align="center"> <!-- Optional demo video link --> ?? <a href="https://youtu.be/example">Demo Video</a> </p>
?? Example Output Log

Connected to LM75 (0x60)
Raw bytes: 0x19 0x00
Temperature: 25.0 °C

??? Notes

    Each bit = 0.5 °C

    Temperatures below 0 °C are encoded in two’s complement

    Uses only standard Linux I?C API: <linux/i2c-dev.h>

    Compatible with any Raspberry Pi model supporting /dev/i2c-1

?? References

    Raspberry Pi I?C Documentation

TI LM75 Datasheet (SNOS675C)

Linux I?C-dev Interface Docs
??? Tags

Raspberry Pi · I2C · Embedded Linux · C Programming · Sensors · Hardware Interfacing
<p align="center"> <sub>?? Project by Leah — exploring low-level sensor communication on embedded systems.</sub> </p> ```