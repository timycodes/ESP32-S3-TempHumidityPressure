#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <U8g2lib.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

// ESP32-S3 I2C pins
#define SDA_PIN 8
#define SCL_PIN 9

// Your elevation in METERS. 
#define ELEVATION_METERS 2133.6   // I'm at 7000 feet

// *** Setup for your Home Wi-Fi network ***
//const char* ssid = "Your_NAME";           // uncomment for local Wi-Fi.
//const char* password = "Your_PASSWORD";   // uncomment for local Wi-Fi.

// *** Setup for a "Hotspot" ***
const char* ap_ssid = "Your_SSID";     // Change
const char* ap_password = "12345678"; // Change ( at least 8 characters )

// Web server on default port 80.  (Usually the IP Address for the Hotspot is 192.168.4.1 (no need to use :80 as it's default)
WebServer server(80);

// OLED display
U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

// BME280 sensor
Adafruit_BME280 bme;

bool bmeFound = false;

// Sensor values
float temperatureF = 0.0;
float humidity = 0.0;
float stationPressureInHg = 0.0;
float seaLevelPressureInHg = 0.0;

void readSensor() {
  float temperatureC = bme.readTemperature();
  temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  humidity = bme.readHumidity();

  float pressure_hPa = bme.readPressure() / 100.0F;
  stationPressureInHg = pressure_hPa * 0.02953;

  float seaLevel_hPa = bme.seaLevelForAltitude(ELEVATION_METERS, pressure_hPa);
  seaLevelPressureInHg = seaLevel_hPa * 0.02953;
}

void updateOLED() {
  display.clearBuffer();

  display.setFont(u8g2_font_6x10_tf);
  display.drawStr(0, 10, "ESP32-S3 Weather");

  display.setCursor(0, 26);
  display.print("Temp: ");
  display.print(temperatureF, 1);
  display.print(" F");

  display.setCursor(0, 40);
  display.print("Hum:  ");
  display.print(humidity, 1);
  display.print(" %");

  display.setCursor(0, 54);
  display.print("SLP:  ");
  display.print(seaLevelPressureInHg, 2);
  display.print(" inHg");

  display.sendBuffer();
}

void handleRoot() {
  readSensor();

  String page = "";
  page += "<!DOCTYPE html>";
  page += "<html>";
  page += "<head>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<meta http-equiv='refresh' content='5'>";
  page += "<title>ESP32-S3 Weather</title>";
  page += "<style>";
  page += "body { font-family: Arial; text-align: center; background: #111; color: white; }";
  page += ".card { background: #222; margin: 15px; padding: 20px; border-radius: 12px; }";
  page += ".value { font-size: 2em; font-weight: bold; }";
  page += "</style>";
  page += "</head>";
  page += "<body>";
  page += "<h1>ESP32-S3 Weather</h1>";

  page += "<div class='card'>";
  page += "<div>Temperature</div>";
  page += "<div class='value'>" + String(temperatureF, 1) + " &deg;F</div>";
  page += "</div>";

  page += "<div class='card'>";
  page += "<div>Humidity</div>";
  page += "<div class='value'>" + String(humidity, 1) + " %</div>";
  page += "</div>";

  page += "<div class='card'>";
  page += "<div>Station Pressure</div>";
  page += "<div class='value'>" + String(stationPressureInHg, 2) + " inHg</div>";
  page += "</div>";

  page += "<div class='card'>";
  page += "<div>Sea-Level Pressure</div>";
  page += "<div class='value'>" + String(seaLevelPressureInHg, 2) + " inHg</div>";
  page += "</div>";

  page += "<p>Page refreshes every 5 seconds.</p>";
  page += "</body>";
  page += "</html>";

  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(SDA_PIN, SCL_PIN);

  display.begin();
  display.clearBuffer();
  display.setFont(u8g2_font_6x10_tf);
  display.drawStr(0, 12, "Starting...");
  display.sendBuffer();

  if (bme.begin(0x76)) {
    bmeFound = true;
    Serial.println("BME280 found at 0x76");
  } else if (bme.begin(0x77)) {
    bmeFound = true;
    Serial.println("BME280 found at 0x77");
  } else {
    bmeFound = false;
    Serial.println("BME280 not found!");
  }

  if (!bmeFound) {
    display.clearBuffer();
    display.drawStr(0, 12, "BME280 Not Found");
    display.drawStr(0, 28, "Check wiring");
    display.sendBuffer();
    while (true);
  }

  display.clearBuffer();
  display.drawStr(0, 12, "Starting Hotspot...");
  display.sendBuffer();

  // SETUP WIFI SECTION ***** 
  // Wi-Fi for home WiFi - ORIGINAL WIFI SETUP AT MEADOW - WORKS. UN/PW.
  
  //WiFi.begin(ssid, password);  << ORIGINAL CODE
  
  // Add ESP32 hotspot mode: creates it own Wi-Fi network
  
  WiFi.softAP("Esp32-Weather", "theMED@120*");

  //Serial.print("Connecting to WiFi");

  //while (WiFi.status() != WL_CONNECTED) {
    //delay(500);
    //Serial.print(".");
  //}

  //Serial.println();
  //Serial.println("WiFi connected!");
  //Serial.print("ESP32 IP address: ");
  //Serial.println(WiFi.localIP());
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password);

IPAddress IP = WiFi.softAPIP();

Serial.println();
Serial.println("ESP32 Hotspot Started");
Serial.print("WiFi Name: ");
Serial.println(ap_ssid);
Serial.print("Password: ");
Serial.println(ap_password);
Serial.print("ESP32 Hotspot IP: ");
Serial.println(IP);


  // Code prints the Wi-Fi IP tp the OLED. ORIGINAL CODE. 
  //display.clearBuffer();
  //display.setCursor(0, 12);
  //display.print("WiFi Connected");

  //display.setCursor(0, 28);
  //display.print("IP:");

  //display.setCursor(0, 44);
  //display.print(WiFi.localIP());

  //display.sendBuffer();

  //server.on("/", handleRoot);
  //server.begin();

  //delay(3000);

  //********* replacing the code with hotspot IP code
  display.clearBuffer();
  display.setFont(u8g2_font_6x10_tf);

  display.setCursor(0, 12);
  display.print("Hotspot Started");

  display.setCursor(0, 28);
  display.print("WiFi:");
  display.print(ap_ssid);

  display.setCursor(0, 44);
  display.print("IP:"); // I took out the IP address 192.168.1.# 
  display.print(IP);

  display.sendBuffer();

  server.on("/", handleRoot);
  server.begin();

  delay(3000);

}

void loop() {
  server.handleClient();

  readSensor();
  updateOLED();

  Serial.print("Temp: ");
  Serial.print(temperatureF, 1);
  Serial.print(" F, Humidity: ");
  Serial.print(humidity, 1);
  Serial.print(" %, SLP: ");
  Serial.print(seaLevelPressureInHg, 2);
  Serial.println(" inHg");

  delay(2000);
}
