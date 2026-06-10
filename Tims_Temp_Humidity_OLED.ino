// Arduino Libraries to install:
// In Arduino IDE go to: Sketch->Include->Manage Libraries.
// Search and add: U8g2, Adafruit BME280 Library, Adafruit_Sensor

// #include <some_library_name.h>  This means bring in these prewritten header files
// so this program can use the functions, classes and definitions inside them.

// I2C communication.

#include <Wire.h>

// U8g2 is the Library. 
// SH1106 is the display's chip/driver inside the OLED display.

#include <U8g2lib.h> 

// BME280 sensor library

#include <Adafruit_BME280.h>

// Brings in the Adafruit Unified Sensor library: the BME280 library depends on it.

#include <Adafruit_Sensor.h>

// ESP32-S3 I2C pins: used for I2C communication. SDA = Serial Data Line, SCL = Serial CLock Line.
// GPIO 8 = I2C data wire.  GPIO 9 = I2C clock wire.
// Both the OLED and the BME280 use the same two I2C signal wires.

#define SDA_PIN 8
#define SCL_PIN 9

// BME280 possible I2C addresses

#define BME_ADDRESS_1 0x76
#define BME_ADDRESS_2 0x77

// OLED display using U8g2
// This is for many DIYmall 1.3 inch OLED displays using SH1106

U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

// BME280 sensor object

Adafruit_BME280 bme;

bool bmeFound = false;

// required 
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Start I2C on ESP32-S3 pins
  Wire.begin(SDA_PIN, SCL_PIN);

  // Start OLED
  display.begin();
  display.clearBuffer();
  display.setFont(u8g2_font_6x10_tf);
  display.drawStr(0, 12, "ESP32-S3 Weather");
  display.drawStr(0, 28, "Starting...");
  display.sendBuffer();
  delay(1000);

  // Start BME280
  if (bme.begin(BME_ADDRESS_1)) {
    Serial.println("BME280 found at 0x76");
    bmeFound = true;
  } 
  else if (bme.begin(BME_ADDRESS_2)) {
    Serial.println("BME280 found at 0x77");
    bmeFound = true;
  } 
  else {
    Serial.println("BME280 not found!");
    bmeFound = false;
  }

  if (!bmeFound) {
    display.clearBuffer();
    display.setFont(u8g2_font_6x10_tf);
    display.drawStr(0, 12, "BME280 Not Found");
    display.drawStr(0, 28, "Check wiring:");
    display.drawStr(0, 42, "SDA GPIO 8");
    display.drawStr(0, 56, "SCL GPIO 9");
    display.sendBuffer();
  } else {
    display.clearBuffer();
    display.setFont(u8g2_font_6x10_tf);
    display.drawStr(0, 12, "BME280 Found!");
    display.drawStr(0, 28, "Starting readings");
    display.sendBuffer();
    delay(1500);
  }
}

void loop() {
  if (!bmeFound) {
    delay(2000);
    return;
  }

  // Read BME280
  float temperatureC = bme.readTemperature();
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  float humidity = bme.readHumidity();
  float pressure_hPa = bme.readPressure() / 100.0F;
  float pressure_inHg = pressure_hPa * 0.02953;

  // Print to Serial Monitor
  Serial.println("----- BME280 Readings -----");
  Serial.print("Temperature: ");
  Serial.print(temperatureF, 1);
  Serial.println(" F");

  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  Serial.print("Pressure: ");
  Serial.print(pressure_inHg, 2);
  Serial.println(" inHg");

  Serial.println();

  // Display on OLED
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
  display.print("Pres: ");
  display.print(pressure_inHg, 2);
  display.print(" inHg");

  display.sendBuffer();

  delay(2000);
}
