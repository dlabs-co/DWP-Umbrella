//Control de los relés.
#include "reles.h"

Rele Bomba1(2);
Rele Bomba2(3);
Rele Bomba3(4);
Rele Bomba4(5);

void setup()
{
 Bomba1.desactiva();
 Bomba2.desactiva();
 Bomba3.desactiva();
 Bomba4.desactiva();

 Bomba1.activa();
 delay(1000);
 Bomba1.desactiva();
 delay(1000);
 Bomba2.activa();
 delay(1000);
 Bomba2.desactiva();
 delay(1000);
 Bomba3.activa();
 delay(1000);
 Bomba3.desactiva();
 delay(1000);
 Bomba4.activa();
 delay(1000);
 Bomba4.desactiva();
 delay(1000);
  
}

void loop() 
{
  
}
