# 🏠 Home Automation Project

##  Overview
This project is a Smart Home Automation system built using:

- Arduino Mega 2560
- ESP8266 (WiFi)
- DHT11 Temperature Sensor
- IR Sensors
- Servo Motor
- Relay (Fan Control)
- Smoke Sensor
- Buzzer
- LED

The system monitors environmental conditions and device status in real time and displays everything on a web dashboard.

---

## ⚙️ Hardware Connections

DHT11      → Pin 7  
Relay      → Pin 30  
IR (Door)  → Pin 8  
Servo      → Pin 9  
Smoke      → Pin 10  
Buzzer     → Pin 11  
IR2        → Pin 12  
LED        → Pin 13  

---

## 🚪 System Flow

1. IR Sensor detects user
2. Servo opens door
3. Temperature is monitored
4. If temperature > threshold → Fan turns ON
5. Smoke detected → Buzzer turns ON
6. IR2 detects object in second room → LED turns ON
7. All system status is sent to ESP8266
8. ESP8266 hosts a web dashboard
9. Dashboard displays:
   - Door Status
   - Temperature
   - Fan Status
   - Smoke Detection
   - Buzzer Status
   - LED Status

---

## 🌐 Web Dashboard

After uploading ESP8266 code:

1. Open Serial Monitor
2. Note the IP address
3. Open browser:
   http://YOUR_IP_ADDRESS

Dashboard auto-refreshes every 3 seconds.

---

## 🔧 How To Upload

### Step 1 – Upload Mega Code
Board: Arduino Mega 2560  
Upload: mega2560_code.ino  

### Step 2 – Upload ESP8266 Code
Board: Generic ESP8266 Module  
Upload: esp8266_webserver.ino  

---

## 📱 Future Improvements
- Control devices from dashboard
- Add mobile app
- Add cloud monitoring
- Add temperature graph
- Add security alerts

---

## 👨‍💻 Author
AKSHAT KUMAR
RAGHAV PURI
ARNAV KUMAR
