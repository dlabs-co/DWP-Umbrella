
#include <Arduino.h>
class Rele
{
  public:
  Rele (uint8_t pin);
  void activa();
  void desactiva();
  private:
  uint8_t _pin;
  private:
};

