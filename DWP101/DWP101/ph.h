/*
 * Libreria dedicada a la sonda de PH
 * 
 * 
 * 
 */
#include <Arduino.h>

#define phx1      4  // PH minimo
#define phx2     10  // PH maximo
#define ty1    403  // RAW maximo (PH 10)
#define ty2    476  // RAW minimo (PH  4)
#define PHraw analogRead(pinPH)

float getPH() 
{
  float     ph=0;
  float      M=0; 
  M= float(ty2 - ty1)/float(phx2 - phx1); //pendiente de la recta
  ph= (((PHraw - ty1)/(M))+ phx1); // valor de ph
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
