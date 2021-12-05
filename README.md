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

Version history, V1 used Air Gradiant lib, but only showed PM 2.5 instead, switched to PMS Lib in order to get 1.0 and 10 
particulate readings.

Version 2, added timers for led/buzzer, and loop, but found out that software serial uses timers,
but learned that ESP8266 only has two timers, one dedicated to wifi, and the other being used by 
the PMS 5003 sensor under software serial. 

Version 3 **in process**, offload warning buzzer, led and timer function to an ATTiny 85