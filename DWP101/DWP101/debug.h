#include <Arduino.h>

#define OK        10
#define NOK       11
#define WIFIOK    20
#define WIFINOK   21
#define RTCOK     30
#define RTCNOK    31
#define DHTOK     40
#define DHTNOK    41
#define LCDOK     50
#define LCDNOK    51
#define PHOK      60
#define PHNOK     61
#define PTOK      70
#define PTNOK     71
#define SDOK      80
#define SDNOK     81

uint8_t debug(String str, uint8_t valor, bool mostrar=true)
{
  if (mostrar)
  {
    dbg.println(str);
  }
  codeError=valor;
  dbg.println("Escribiendo en SD");
  myLog = SD.open("log.txt", FILE_WRITE);
  myLog.println(fecha +";" + hora + ";" + String(codeError)+";"+ str);
  myLog.close();
  return valor;
}

void testSecuence()
{
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
