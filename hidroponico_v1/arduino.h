/*
Programa para el control de un cultivo hidropónico
Primera fase.
Toma de datos y control , poner la información en una página web
Datos.
.- PH (falta la sonda
.- Temperatura del líquido PT100 controlada la información por un amplificador
operacional INA122A
.- Reloj de tiempo real 
.- Tmperatura y humedad ambiente unsando un DHT22
.- Información en web por un módulo ESP8266
Programa realizado por 
Luis Gerardo Ramón Hernández
Pablo Aliaga Cremades
Zaragoza a 2016/08/05
*/

#define ARDUINO_PROG "Control de cultivo hidropónico"
#define VERSION "Version 1_0_1"
void informacion()
{
  dbg.println(ARDUINO_PROG);
  dbg.println(VERSION);
}

