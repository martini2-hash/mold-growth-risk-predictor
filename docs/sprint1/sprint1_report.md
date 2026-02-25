# Sprint 1 Report – Mold Risk Monitor

## Objective
The goal of Sprint 1 was to learn how to interface a sensor with the ESP32 and collect 
environmental data related to mold risk, specifically temperature and humidity.

---

## What I Did
- Set up Arduino IDE and configured ESP32 board support
- Connected the AHT10 temperature and humidity sensor using I2C communication
- Verified sensor connection using an I2C scanner
- Read real-time temperature and humidity data from the sensor
- Converted temperature from Celsius to Fahrenheit
- Structured output to show data over time

---

## System Overview
- Microcontroller: XIAO ESP32-C6
- Sensor: AHT10 (Temperature & Humidity)
- Communication Protocol: I2C
- Output: Serial Monitor (real-time data)

---

## Results
The system successfully reads and displays real-time environmental data.

Example output:
- Temperature: ~74°F
- Humidity: ~25%

Data updates every 2 seconds and shows consistent readings over time.

---

## Challenges
- Initial wiring mistakes (incorrect 3.3V connection)
- I2C device not detected at first
- Confusion with pin mapping (GPIO vs D pins)
- Library mismatch (installed wrong AHT10 library initially)

---

## What I Learned
- How I2C communication works between ESP32 and sensors
- Importance of correct wiring and power connections
- How to debug hardware and software issues
- How to use libraries to interact with sensors
- How to structure data output for analysis

---

## What is next (Sprint 2)
- Build a web application to visualize temperature and humidity data
- Display trends over time
- Add indicators for high humidity levels
- Begin connecting ESP32 to WiFi for data transmission
