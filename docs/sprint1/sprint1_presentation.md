---
marp: true
title: Sprint 1 – Mold Risk Monitor
author: Idalia Martin
theme: default
paginate: true
---

# Sprint 1 – Mold Risk Monitor

AI-Driven IoT System Development  
Idalia Martin

---

## Objective

- Learn how to interface a sensor with ESP32
- Collect temperature and humidity data
- Understand I2C communication

---

## What I Built

- ESP32 (XIAO ESP32-C6)
- AHT10 temperature & humidity sensor
- I2C communication setup
- Real-time data output
---

## System Overview

- Sensor collects environmental data
- ESP32 reads data via I2C
- Data displayed in Serial Monitor
- Updates every 2 seconds

---

## Results

- Successfully read temperature and humidity
- Example:
  - Temperature: ~74°F
  - Humidity: ~25%
- Data shows patterns over time

---

## Challenges

- Wiring issues (3.3V connection)
- I2C not detected initially
- Pin mapping confusion
- Library installation issue

---

## Next Steps

- Build web dashboard
- Visualize trends
- Add humidity alerts
- Connect ESP32 to WiFi

---

## Thank You

Any questions?