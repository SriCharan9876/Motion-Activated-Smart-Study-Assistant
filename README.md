# Motion-Activated Smart Study Assistant  
**Board:** Raspberry Pi Pico  
**Cloud Platform:** Adafruit IO  
**Simulation / Demo Link:** https://wokwi.com/projects/421667198122618881

---

## 🧠 Introduction
The Motion-Activated Smart Study Assistant helps students **track study sessions** using a PIR sensor.  
It records study time, detects inactivity, and provides real-time monitoring on an OLED display.  
The system integrates with **Adafruit IO** for cloud logging and sends SMS alerts for prolonged inactivity.

---

## ⚙️ Components
1. Raspberry Pi Pico  
2. PIR Sensor (Motion Detection)  
3. LED (Study Indicator)  
4. Buzzer (Inactivity Alert)  
5. OLED Display (128x64)  
6. Wi-Fi Module (ESP8266 via network library)  

---

## 🚩 Problem Statement
Students often lose track of study time and take prolonged breaks, leading to inefficiency.  
A system is needed to monitor study sessions and alert users when inactive for too long.

---

## 💡 Proposed Solution
- Detects motion using a PIR sensor and logs **study time**.  
- Triggers **LED indicator** and **buzzer alerts** on inactivity.  
- Sends **SMS notifications** via Adafruit IO.  
- Logs study time and alert status on the cloud for **remote monitoring**.

---

## 🧩 Key Functionalities
| Feature | Description |
|---------|-------------|
| 👀 Motion Detection | PIR sensor tracks user activity |
| 💡 Visual Feedback | LED indicates active study session |
| 🔔 Inactivity Alert | Buzzer and SMS notifications for prolonged inactivity |
| 🖥️ OLED Display | Shows real-time study time and alert status |
| 🌐 Cloud Integration | Adafruit IO stores study data and triggers remote alerts |

---

## 🧰 Libraries / Technologies Used
- MicroPython  
- `network`, `urequests`  
- `ssd1306` for OLED Display  
- Adafruit IO API for cloud logging and SMS alerts  

---

