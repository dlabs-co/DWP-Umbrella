

#include <DHT.h>
#include <Wire.h>
#include <FaBoLCD_PCF8574.h>

#define wifi Serial3
#define dbg Serial

FaBoLCD_PCF8574 lcd;


float temperatura;
float humedad;


#define DHTPIN A7
#define DHTTYPE DHT22


DHT dht(DHTPIN,DHTTYPE);


#include "define_wifi.h"
#include "web_server.h"
void setup() 
{
  wifi.begin(9600);
  dbg.begin(9600);
  lcd.begin(16,2);
  lcd.print("Hidroponico");
  lcd.setCursor(0,0);
  dbg.println("Empezando");
  if (conectar(10000))
  {
    lcd.print("Conectado a " + String (SSID));
  }
  else
  {
    lcd.print("Error conexion");
  }
  
  delay(1000);
}

#define BUFFER_SIZE 512

#define runEvery(t) for (static uint32_t _lasttime;(uint32_t)((uint32_t)millis()- _lasttime) >=(t); _lasttime+=(t))

void loop()
{
  
  char buffer[BUFFER_SIZE] = {};
  String auxBuffer;

  runEvery(5000)
  {
    temperatura = dht.readTemperature();
    humedad = dht.readHumidity();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: "+ String(temperatura));
    lcd.setCursor(0,1);
    lcd.print("Hum: "+ String(humedad));
    
  }
  int ch_id, packet_len;
  if (wifi.readBytesUntil('\n', buffer, BUFFER_SIZE) > 0)
  {
    
    temperatura = dht.readTemperature();
    humedad = dht.readHumidity();
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
//        parserNivel2(auxBuffer);

        webServer(ch_id);
      }
    }
  }

}
