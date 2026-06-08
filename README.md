# Project goal
  Take a ESP32-S3 combined with an I2C OLED display and BME280 sensor that sends
  data to  both a smartphone and computer.

# ESPRESSIF ESP32-S3-WROOM-1
  The sqaure metal-can module located at top of the board with writing on it contains the
  ESP32-S3 microcontroller (MCU)unit or System on Chip (SoC): it is both because it includes the 
  processor, memory support, Wi-Fi, Bluebooth and other hardware features in one chip/module. 

  ## Feature : Specification
  - The board uses an Espressif ESP32-S3_WROOM-1 MODULE:
  1. MCU/PROCESSOR: ESP32-S3 (MY Variant: N8R8; 8 MB flash / 8 MB PSRAM configuration).
  2. R8 = 8 MG PSRAM
  3. OPI PSRAM: the OPI means: Octal Peripheral Interface. In plain English: "the
        ESP32-S3 talks to the external PSRAM using 8-bit-wide data connection.
  4. Think of it like lanes on a road:
         SPI = fewer lanes
         OPI = 8 lanes.
  
  
  3. CPU core: Dual-core Xtensa LX7
  4. CPU speed: Up to 240 MHz
  5. Architecture: 32-bit
  6. WiFi:  2.4 GHz 802.11 b/g/n
  7. Bluetooth:  BLE 5 ( Bluetooth 5 Low Energy )
  8. Internal SRAM: 512 KB
  9. ROM: 384 KB
  10. RTC SRAM: 16 KB
  11. GPIO PINS : up to 36 on ESP32-S3-WROOM-1
  12. USB: NATIVE USB SUPPORT: depends on board wiring.
  13. ADC: Analog input support
  14. Interfaces: I2C, SPI, UART, I2S, PWM, ADC, USB, etc.
  15. Antenna: Built-in PCB antenna on the module.
  
 

# Small I2C OLED display: 0.96-inch 128x64 OLED display using the SSD1306 driver.
  Four Pins:
  1. VCC: Power.
  2. GND: Ground.
  3. SCL: Clock.
  4. SDA: Data

  Interface: I2C

  Size: 0.96 inches
  Resolution: 128x64
  Driver: SSD1306 (some similar-looking OLED's use the SH1106 driver)


  SSD1306 is the controller chip part number made by Solomon Systech.
  When people say, "SSD1306 OLED" they mean: "An OLED display module that uses the SSD1306 controller chip".

  
