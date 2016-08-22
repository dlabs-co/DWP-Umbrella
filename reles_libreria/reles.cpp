#include "reles.h"


Rele::Rele(uint8_t pin)
{
  pinMode(pin,OUTPUT);
  _pin=pin;
  //pinMode(_pin,LOW);
}

void Rele::activa()
{
  digitalWrite(_pin,LOW);
}

void Rele::desactiva()
{
  digitalWrite(_pin,HIGH);
}


