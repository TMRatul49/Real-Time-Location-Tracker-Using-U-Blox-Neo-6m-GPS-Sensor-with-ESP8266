#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

const char* ssid = "Your WiFi SSID";
const char* password = "Your WiFi Password";

// Create Firebase config and auth objects
FirebaseConfig config;
FirebaseAuth auth;

// GPS pins
#define RX 14
#define TX 12
#define GPS_BAUD 9600

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RX, TX);

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(GPS_BAUD);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  // Firebase configuration
  config.api_key = "Your Firebase Project API Key";
  config.database_url = "Your Firebase Project Database URL";

  // Anonymous sign-in (no email/password)
  auth.user.email = "Your Firebase Project User Mail";
  auth.user.password = "Your Firebase Project User Password";

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  unsigned long start = millis();

  while (millis() - start < 1000) {
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }

    if (gps.location.isUpdated()) {
      double lat = gps.location.lat();
      double lng = gps.location.lng();
      double speed = gps.speed.kmph();
      double alt = gps.altitude.meters();
      double hdop = gps.hdop.value() / 100.0;
      int sats = gps.satellites.value();

      String dateTime = String(gps.date.year()) + "/" + String(gps.date.month()) + "/" + String(gps.date.day()) + " " + String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second());

      // ----- Serial Output -----
      Serial.print("LAT: ");
      Serial.println(lat, 6);
      Serial.print("LONG: ");
      Serial.println(lng, 6);
      Serial.print("SPEED (km/h): ");
      Serial.println(speed);
      Serial.print("ALT (m): ");
      Serial.println(alt);
      Serial.print("HDOP: ");
      Serial.println(hdop);
      Serial.print("Satellites: ");
      Serial.println(sats);
      Serial.print("Time (UTC): ");
      Serial.println(dateTime);
      Serial.println();

      // ----- Firebase Upload -----
      Firebase.setDouble(firebaseData, "/gps/latitude", lat);
      Firebase.setDouble(firebaseData, "/gps/longitude", lng);
      Firebase.setDouble(firebaseData, "/gps/speed", speed);
      Firebase.setDouble(firebaseData, "/gps/altitude", alt);
      Firebase.setDouble(firebaseData, "/gps/hdop", hdop);
      Firebase.setInt(firebaseData, "/gps/satellites", sats);
      Firebase.setString(firebaseData, "/gps/time", dateTime);
    }
  }
}
