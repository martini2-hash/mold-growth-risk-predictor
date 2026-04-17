# Mold Growth Risk Predictor

## Project Overview
This project is an AI-assisted IoT system that monitors temperature and humidity to assess mold growth risk in indoor environments.

Mold growth is a common issue in homes, apartments, and dorms, especially in areas with poor ventilation or high humidity. Early awareness of mold-friendly conditions can help users take preventive action before damage or health risks occur.

This project focuses on **building a functional IoT system with AI-assisted development**, rather than implementing advanced machine learning models.

---

## Problem Statement
Mold growth often occurs unnoticed until it becomes visible or causes health issues. Many people do not continuously monitor indoor humidity and temperature, which are key contributors to mold growth.

This project provides users with real-time insights into environmental conditions and helps them recognize patterns that may increase mold growth risk.

---

## Current Features
- Real-time temperature and humidity monitoring using an AHT10 sensor
- ESP32-based data collection and WiFi communication
- Web dashboard accessible through a browser
- Mold risk classification (Low, Moderate, High)
- Trend detection (Rising, Falling, Stable humidity)
- Recent readings history
- Humidity trend visualization (graph)
- Styled user interface with a consistent color palette

---

## Technologies and Tools

### Hardware
- Seeed Studio XIAO ESP32-C6
- AHT10 temperature and humidity sensor
- Breadboard and jumper wires

### Software
- Arduino IDE
- Embedded C++ (ESP32)
- HTML, CSS, JavaScript (served by ESP32)
- GitHub for version control

### AI Tools
- AI assistance for:
  - code generation
  - debugging hardware/software issues
  - learning new concepts (I2C, web server, etc.)
  - UI and dashboard design improvements

---

## System Architecture
AHT10 Sensor → ESP32 (Data Processing) → Web Server → Browser Dashboard

- The sensor collects environmental data
- The ESP32 processes and stores recent readings
- A built-in web server serves a dashboard
- The user accesses the dashboard via a browser

---

## Project Scope
This project focuses on identifying environmental conditions that support mold growth based on humidity and temperature trends.

It does **not**:
- Detect actual mold presence
- Provide medical or health diagnoses

---

## Project Status
Sprint 1:
- Sensor integration (AHT10)
- I2C communication setup
- Real-time data collection

Sprint 2:
- WiFi connectivity
- Web dashboard implementation
- Mold risk classification
- Trend detection
- Graph visualization
- UI/UX improvements

The system is now a **working IoT prototype** capable of real-time environmental monitoring and visualization.

---

## Future Improvements
- Long-term data storage
- Advanced trend analysis
- Mobile-friendly UI
- Alerts/notifications for high humidity
- Deployment to a public web interface

