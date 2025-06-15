# 📍 Real-Time GPS Location Tracker with ESP8266 & Firebase

A lightweight and accurate real-time location tracking system using **U-Blox Neo 6M GPS module**, **ESP8266 NodeMCU**, and **Firebase Realtime Database**. It continuously pushes live latitude and longitude data to Firebase—ideal for location-aware IoT projects, asset tracking, or DIY geofencing experiments.

---

## 🛰️ Hardware Required

| Component              | Quantity |
|------------------------|----------|
| ESP8266 NodeMCU        | 1        |
| U-Blox Neo 6M GPS      | 1        |
| Jumper Wires           | as needed |
| 5V Power Supply        | 1        |

---

## 🔌 Circuit Connections

| GPS Module Pin | ESP8266 Pin |
|----------------|-------------|
| VCC            | 3V3 or Vin  |
| GND            | GND         |
| TX             | D7 (GPIO13) |
| RX             | D8 (GPIO15) |

> ⚠️ Note: The GPS module communicates via serial. SoftwareSerial is used to avoid interfering with ESP8266’s default serial port.

---

## ☁️ Firebase Setup

1. Go to [Firebase Console](https://console.firebase.google.com)
2. Create a new project
3. Navigate to **Realtime Database > Create Database**
4. In "Rules", allow read/write temporarily:
   ```json
   {
     "rules": {
       ".read": true,
       ".write": true
     }
   }

5. Grab your:

 - Database URL

 - Secret / API Key (if needed for authentication)

6. Insert these into your .ino file where required

---

## 📡 How It Works

- The Neo 6M GPS module locks satellite coordinates.

- The ESP8266 reads the GPS data via SoftwareSerial.

- Latitude and Longitude are parsed from the NMEA sentence.

- The data is sent to Firebase in real-time.

---

## 📂 Project Structure

```
esp8266-gps-tracker/
├── gps_sensor_esp8266_firebase.ino
├── README.md
└── (optional) circuit-diagram.png
```

---

## 📱 Optional Enhancements
- 🌍 Generate a Google Maps link with the coordinates

- 🗺️ Visualize data using a web dashboard with Leaflet.js or Google Maps API

- 🧭 Add direction/speed tracking from GPS sentences

---

## 🤖 Built By

Made with 💡 by [@TMRatul49](https://github.com/TMRatul49)  
📧 Contact: [tmmehrabhasan@gmail.com](mailto:tmmehrabhasan@gmail.com)
