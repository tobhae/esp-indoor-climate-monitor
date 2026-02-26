# Distributed Indoor Climate Monitor System

Battery-powered distributed indoor climate monitoring system built with ESP8266 microcontroller and BME280 environmental sensor. 

Each node collects temperature, humidity, and pressure data and transmits measurements over WiFi to an InfluxDB database. Data is visualized using Grafana for real-time and historical analysis.

## Architecture

ESP8266 Node → InfluxDB (Docker) → Grafana Dashboard

## Tech Stack

- ESP8266 firmware (Arduino framework)
- BME280 sensor (I2C)
- InfluxDB 2.7 (Docker)
- Grafana (Docker)
- Li-Ion 18650 battery power

## Status

Work in progress.  

Firmware and infrastructure are being actively refined.
Project structure and documentation will be expanded as development progresses.