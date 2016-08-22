
#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <FaBoLCD_PCF8574.h>
#include <RtcDS3231.h>
#include <SD.h>
#include <SPI.h>

RtcDS3231 Rtc;
FaBoLCD_PCF8574 lcd; // initialize the library
File myLog;
#define DHTTYPE DHT22


#define wifi Serial3
#define dbg  Serial
#define DEBUG true

#include "schedule.h"
#include "pins.h"

#include "relays.h"

#define runEvery(t) for (static uint32_t _lasttime;(uint32_t)((uint32_t)millis()- _lasttime) >=(t); _lasttime+=(t))

Rele Bomba1(pinRele1);
Rele Bomba2(pinRele2);
Rele Bomba3(pinRele3);
Rele Bomba4(pinRele4);


#include "debug.h"
#include "ds3231.h"
#include "lcd.h"
#include "ph.h"
#include "temp.h"

DHT dht(pinDHT,DHTTYPE);
float temperatura;
float humedad;

#include "define_wifi.h"
#include "web_server.h"
#include "buzzer.h"


