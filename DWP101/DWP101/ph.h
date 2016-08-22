/*
 * Libreria dedicada a la sonda de PH
 * 
 * 
 * 
 */
#include <Arduino.h>

#define x1      4  // PH minimo
#define x2     10  // PH maximo
#define y1    403  // RAW maximo (PH 10)
#define y2    476  // RAW minimo (PH  4)
#define PHraw analogRead(pinPH)

float getPH() 
{
  float     ph=0;
  float      M=0; 
  M= float(y2 - y1)/float(x2 - x1); //pendiente de la recta
  ph= (((PHraw - y1)/(M))+ x1); // valor de ph
  debug("PH: " + String(PHraw), PHNOK, DEBUG);
  if (ph<4 || ph>10)
  {
      debug("PH: " + String(ph), PHNOK, DEBUG);
  }
  else 
  {
      debug("PH: " + String(ph), PHOK, DEBUG);
  }
  return ph;
}
