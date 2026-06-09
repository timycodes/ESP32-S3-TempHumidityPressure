# My ESP Weather Project
  This project reads temperature, humidity, and pressure using an ESP32 and a BME280 sensor.

## ESPRESSIF ESP32-S3-WROOM-1
  - The square metal-can module located at top of the board with writing on it contains the
    ESP32-S3 microcontroller (MCU)unit or System on Chip (SoC): it is both because it
    includes the processor, memory support, Wi-Fi, Bluebooth and other hardware features
    in one chip/module. 

  ### Features : Specification
  **The board is an Espressif ESP32-S3_WROOM-1 MODULE**
  1. MCU/PROCESSOR: ESP32-S3 
     #### MY Variant: N8R8; 8 MB flash / 8 MB PSRAM configuration.
     - N8 = 8 MG **built-in flash memory** (stores your program/code/sketch).
       --  Keeps data after power off.
     - RAM = Temporary working memory. (On power OFF: data erased.)
     - R8 = 8 MG **PSRAM** (Extra temporary working memory) (On power OFF: data erased.)
  3. OPI PSRAM: the OPI means: **Octal Peripheral Interface.**
     - In plain English: "the
        ESP32-S3 talks to the external PSRAM using 8-bit-wide data connection.
     - Think of it like lanes on a road:
         SPI = fewer lanes
         OPI = 8 lanes.
  
  
  4. CPU core: Dual-core Xtensa LX7
  5. CPU speed: Up to 240 MHz
  6. Architecture: 32-bit
  7. WiFi:  2.4 GHz 802.11 b/g/n
  8. Bluetooth:  BLE 5 ( Bluetooth 5 Low Energy )
  9. Internal SRAM: 512 KB
  10. ROM: 384 KB
  11. RTC SRAM: 16 KB
  12. GPIO PINS : up to 36 on ESP32-S3-WROOM-1
  13. USB: NATIVE USB SUPPORT: depends on board wiring.
  14. ADC: Analog input support
  15. Interfaces:
      - I2C,
      - SPI,
      - UART,
      - I2S,
      - PWM,
      - ADC,
      - USB, 
  17. Antenna: Built-in PCB antenna on the module.
  
 

## Small I2C OLED display: 0.96-inch 128x64 OLED display using the SSD1306 driver.
  1. Four Pins:
  - VCC: Power.
  - GND: Ground.
  - SCL: Clock.
  - SDA: Data.

  2. Interface: I2C

  3. Size: 0.96 inches
  4. Resolution: 128x64
  5. Driver: SSD1306 **(some similar-looking OLED's use the SH1106 driver)**


  **SSD1306 is the controller chip part number made by Solomon Systech.
  When people say, "SSD1306 OLED" they mean: "An OLED display module that uses the SSD1306 controller chip".**

  
