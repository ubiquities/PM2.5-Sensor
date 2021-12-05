/*
Project outline:
Components
1. 1.3" I2C OLED screen (I2C address Ox3C)
2. BME280 temperture and humidity sensor (I2C address Ox78)
3. PMS5003 - PM 2.5 particulate sensor

Hardware setup
1. 50x70 mm through hole proto board
2. wired BME280 and OLED via I2C on Wemos D1-D2 pins
3. PMS5002 via software Serial on pins D5, D6
4. wired buzzer on D0, with inline switch under the Wemosin case it gets annoying
5. wired LED on D7
6. Modeled housing and printed

Code taken from Libraraies:
1. PMS Library by Mariusz Kacki
2. Adafruit BME sensor 
3. non-blocking timer: https://eloquentarduino.github.io/2019/12/non-blocking-arduino-code/
*/

// Air Sensor setup
#include "PMS.h"
#include "SoftwareSerial.h"
SoftwareSerial pmsSerial(14, 12); // RX, TX trying to use GPIO number i/o wemos pin #
PMS pms(pmsSerial);
PMS::DATA data;

// BME280 Sensor setup
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // use I2C interface

// Display Setup
#include <Adafruit_SH110X.h>   // OLED display library
//#include <Adafruit_GFX.h>       // Graphics for rectangle bar graph// For LED status
#define i2c_Address 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//Global Variable
#define every(interval) \
    static uint32_t __every__##interval = millis(); \
    if (millis() - __every__##interval >= interval && (__every__##interval = millis()))

#define Millis 
#define Second  *1000
#define Seconds *1000
int interval = 1 Second;
#define LED D7
#define buzzer D8


void setup(){
pinMode(LED, OUTPUT);
pinMode(buzzer, OUTPUT);
digitalWrite(LED, LOW);
digitalWrite(buzzer, LOW);
  
  Serial.begin(115200);
  pmsSerial.begin(115200);

  // OLED Setup
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(i2c_Address, true)) { // Address 0x3C default
      Serial.println(F("Display allocation failed"));
  }

  display.display();
  delay(2000);
  display.clearDisplay();

  Serial.println(F("BME280 Sensor event test"));

unsigned status;
    // You can also pass in a Wire library object like &Wire2
    status = bme.begin(0x76);

  if (!status) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    while (1) delay(10);
  } else {
    Serial.println(F("BME280 sensor initiated successfully"));
  }

}

void loop(){
   every(5000 Millis) {

if (pms.read(data)) {
Serial.print("read data code read");
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
  if ((data.PM_AE_UG_2_5) >= 35 || (data.PM_AE_UG_10_0) >= 135) {
    display.setTextColor(SH110X_BLACK, SH110X_WHITE); // 'inverted' text
    display.invertDisplay(true);
    //highLevels();
  } else {
  //display.setTextColor(SH110X_WHITE); //required otherwise blank screen
  display.invertDisplay(false);
  }
  display.setTextSize(1);
display.setCursor(0, 0);
//display.print("PM2: ");
//display.println(PM25Global);

    display.println("PM1.0 :" + String(data.PM_AE_UG_1_0) + "(ug/m3)");
    display.println("PM2.5 :" + String(data.PM_AE_UG_2_5) + "(ug/m3)");
    display.println("PM10  :" + String(data.PM_AE_UG_10_0) + "(ug/m3)");


  //display.setTextSize(1); 
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


  } else {
    Serial.println("No PM2.5 Module Data found, check wiring"); 
  }

}
}



//void highLevels() {
//  every(1000 Millis){
//   digitalWrite(LED, HIGH);
//   delay(100);
//   digitalWrite(LED, LOW);
//  }
//
//  every(60000 Millis) {
//   tone(buzzer, 1500);
//   delay(10);
//   noTone(buzzer);
//  }
//}
