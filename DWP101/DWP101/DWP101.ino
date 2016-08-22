/*
 * Software and Electronic With Sor_maria and Lugerh 
 * Proyect developed in Dlabs Hackerspace (Dlabs.co)
 * #define Sor_maria Pablo Aliaga Cremades
 * #define Lugerh Luis Gerardo Ramón Henández
 */
#include <Arduino.h> 
#define BUFFER_SIZE 512
uint8_t codeError = -1;
String lastState;
char buffer [BUFFER_SIZE]={};
String auxBuffer;
String hora;
String fecha;

#include "config.h"
                // Objeto fichero

void setup()
{
  hardReset();
  //testSecuence();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2); // Inicializar LCD
  dbg.begin(9600);  // Inicializar Serial USB
  wifi.begin(9600); // Inicializar Serial WIFI

  // Iniciar con las salidas desactivadas
  Bomba1.desactiva();
  Bomba2.desactiva();
  Bomba3.desactiva();
  Bomba4.desactiva();
  // Print a message to the LCD.
  seeBanner();             // DWP hidroponico
  seeBannerDlabs();        // in cooperation with dlabs.co
  if (!SD.begin(22))
  {
    debug("initialization failed!", SDNOK, DEBUG);
  }
  else debug("SD Initialization OK!", SDOK, DEBUG);
  
  if (conectar(10000))
  {
    debug("WIFI conectada:"+String (SSID), OK, DEBUG);
    printState("WIFI:" + String (SSID));
    delay(2000);
  }
  else
  {
    debug("Error conexion", WIFINOK, DEBUG);
    printState("Error conexion");
    delay(2000);
  }
  seeHour();               // Mostrar Hora
  printState("System OK"); 
}

void loop()
{
////////    Servidor WEB   No tocar!!!!    ///////////
  int ch_id, packet_len;
  if (wifi.readBytesUntil('\n', buffer, BUFFER_SIZE) > 0)
  {
    ///// falta quitar
    //temperatura=10; // = dht.readTemperature();
    //humedad=10; //= dht.readHumidity();
    ///// END falta quitar
    dbg.println("......datos recibidos......");
    dbg.println(buffer);
    if (strncmp(buffer, "+IPD,", 5) == 0) //Peticion de conectividad
    {
      sscanf(buffer+5,"%d,%d",&ch_id,&packet_len);
      auxBuffer = String (buffer);
      if (auxBuffer.indexOf("favicon.ico")==-1)//evitamos cargar cuando el navegador haga la petición del favicon.ico
      {
        auxBuffer = auxBuffer.substring(auxBuffer.indexOf(":GET")+6,auxBuffer.indexOf("HTTP")-1)+"&";
        dbg.println(auxBuffer);  
//        parserNivel2(auxBuffer); // no tocar, lectura dedatos de la web
        webServer(ch_id);
        printState("Server UP");
      }
    }
  }
  
////////   END Servidor WEB   No tocar!!!!    ///////////  
  else
  {
         ///////   usar TIMERRRRRRR o eliminar baners
    runEvery(5000)         //repeat every 5s
    {
     // seeBanner();         // print banner
      seeHour();           // print date & hour
      temperatura = dht.readTemperature();
      humedad = dht.readHumidity();
      printState("T:" + String(temperatura).substring(0,4) + "C  H:" + String(humedad).substring(0,4) + "%");
      dbg.println("T:" + String(temperatura).substring(0,4) + "C  H:" + String(humedad).substring(0,4) + "%");
      getPH();
      getTemp();
      //defcon1();
      //defcon1();
      debug(String(codeError), OK, DEBUG);
      //testSecuence();
      if (compare_hour(hora_inicio_1, minuto_inicio_1, hora_fin_1, minuto_fin_1))
      {
        Bomba1.activa();
        debug("bomba1.activa",OK, DEBUG);
      }
      else 
      {
        Bomba1.desactiva();
        debug("bomba1.inactiva",NOK, DEBUG);
      }
      if (compare_hour(hora_inicio_2, minuto_inicio_2, hora_fin_2, minuto_fin_2))
      {
        Bomba2.activa();
        debug("bomba2.activa",OK, DEBUG);
      }
      else 
      {
        Bomba2.desactiva();
        debug("bomba2.inactiva",NOK, DEBUG);
      }
      if (compare_hour(hora_inicio_l, minuto_inicio_l, hora_fin_l, minuto_fin_l))
      {
        Bomba4.activa();
        debug("bomba4.activa",OK, DEBUG);
      }
      else 
      {
        Bomba4.desactiva();
        debug("bomba4.inactiva",NOK, DEBUG);
      }
    }
  }
}
