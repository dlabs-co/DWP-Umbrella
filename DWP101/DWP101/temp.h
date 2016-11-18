/*
   Libreria dedicada a la sonda PT-100

            (temperatura)

*/
#include <Arduino.h>

#define tx1      0  // Temp minimo
#define tx2     75  // Temp maximo
#define ty1    118  // RAW maximo (Temp )
#define ty2    720// RAW minimo (Temp )
#define Traw analogRead(pinPT)
#define Tmin 17
#define Tmax 40

float getTemp()
{
  float     temp = 0;
  float        M = 0;
  M = float(ty2 - ty1) / float(tx2 - tx1); //pendiente de la recta
  temp = (((Traw - ty1) / (M)) + tx1); // valor de ph
  debug("RAW: " + String(Traw), PHOK, DEBUG);
  debug("Temp: " + String(temp), PHOK, DEBUG);
  if (temp<Tmin || temp>Tmax)
  {
      debug("Temp: " + String(temp), PTNOK, DEBUG);
  }
  else 
  {
      debug("Temp: " + String(temp), PTOK, DEBUG);
  }
  return temp;
}

//   0 ---- 118 ---- 117 ---- 119
//  26 ---- 354 ---- 355 ---- 354
//  75 ---- 721 ---- 723 ---- 724  
