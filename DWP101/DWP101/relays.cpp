#include "relays.h"

Rele::Rele(uint8_t pin)
{
  pinMode(pin,OUTPUT);
  _pin=pin;
  digitalWrite(_pin,HIGH);
}

void Rele::activa()
{
  digitalWrite(_pin,LOW);
}

void Rele::desactiva()
{
  digitalWrite(_pin,HIGH);
}
