/*
This is the code for the AirGradient DIY Air Quality Sensor with an ESP8266 Microcontroller.

It is a high quality sensor showing PM2.5, CO2, Temperature and Humidity on a small display and can send data over Wifi.

For build instructions please visit https://www.airgradient.com/diy/

Compatible with the following sensors:
Plantower PMS5003 (Fine Particle Sensor)

Please install ESP8266 board manager (tested with version 3.0.0)

If you are a school or university contact us for a free trial on the AirGradient platform.
https://www.airgradient.com/schools/

MIT License

Project outline:
Components
1. 1.3" I2C OLED screen (I2C address Ox3C)
2. BME280 temperture and humidity sensor (I2C address Ox78)
3. PMS5003 - PM 2.5 particulate sensor

Code taken from Libraraies:
1. Airgradient PM2_Sample
2. Adafruit BME sensor 
*/

// Air Sensor setup
#include <AirGradient.h>
AirGradient ag = AirGradient();

// BME280 Sensor setup
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // use I2C interface

// Display Setup
#include <Adafruit_SH110X.h>   // OLED display library
//#include <Adafruit_GFX.h>       // Graphics for rectangle bar graph// For LED status
#define i2c_Address 0x3c
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//Global Variable
int PM25Global = 0;

void setup(){
  Serial.begin(115200);
  ag.PMS_Init();

  // OLED Setup
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(i2c_Address, true)) { // Address 0x3C default
      Serial.println(F("Display allocation failed"));
    for (;;); // Don't proceed, loop forever
  } else {
    Serial.println(F("Display connected"));
  }
  display.display();
  delay(1000);
  display.clearDisplay();

  Serial.println(F("BME280 Sensor event test"));

bool status;
    // You can also pass in a Wire library object like &Wire2
    status = bme.begin(0x76);

//  if (!bme.begin()) {
//    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
//    while (1) delay(10);
//  }

}

void loop(){
    
int PM2 = ag.getPM2_Raw();
Serial.print("PM2: ");
Serial.println(ag.getPM2());
PM25Global = PM2;

  Serial.print(F("Temperature = "));
  Serial.print(1.8 * bme.readTemperature() + 32);
  Serial.println(" *F");

  Serial.print(F("Humidity = "));
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print(F("Pressure = "));
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.println();

// Oled display functions  
  display.clearDisplay();
  delay(1);
  display.setTextColor(SH110X_WHITE); //required otherwise blank screen
  display.setTextSize(2);
  display.setCursor(0, 8);
display.print("PM2: ");
display.println(PM25Global);
  display.setTextSize(1); 
  display.println();
  display.print(F("Temp: "));
  display.print(1.8 * bme.readTemperature() + 32);
  display.println(" F");

  display.print(F("Humidity: "));
  display.print(bme.readHumidity());
  display.println(" %");

  display.print(F("Pressure: "));
  display.print(bme.readPressure() / 100.0F);
  display.println(" hPa");
  display.display();

delay(5000);
}
