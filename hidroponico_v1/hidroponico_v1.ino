//Libreria para el control de temperartura y humedad ambiente

#include <DHT.h>

#define dbg Serial

#include "arduino.h"

#define DHTPIN A
void setup() 
{
  Serial.begin(9600);
  informacion();
}

void loop() 
{

}
