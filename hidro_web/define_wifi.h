#define SSID "Dlabs"
#define PASSWORD_WIFI "dellmacmolaano"


String ordenesESP[]=
{
"AT+CWMODE=1",                                                       //modo cliente
  "AT+CWJAP=\"" + String(SSID)+ "\",\""+ String(PASSWORD_WIFI)+"\"",
  "AT+CIPSTA=\"192.168.1.45\",\"192.168.1.1\",\"255.255.255.0\"",  // IP static, Gateway, Netmask
  "AT+CIFSR",                                                        // Muestra IP
  "AT+CIPMUX=1",                                                     // Modo Multiconexión
  "AT+CIPSERVER=1,80",                                               // Abre puerto 80
  "AT",                                                              // OK
  "END",                                                             // Cierra envio de ordenes
};


String getLineWifi()
{
  String s="";
  if (wifi.available())
  {
    char c= wifi.read();
    while (c!='\n')
    {
      s+=c;
      delay(25);
      c=wifi.read();
    }
    return s;
  }
}


bool conectar(long timeOut)
{
  Serial.println("WIFI");
  int i=0;
  bool conectado=true;
  while (ordenesESP[i]!="END")
  {
    dbg.println(ordenesESP[i]);
    wifi.println(ordenesESP[i++]);
    
    long flag=millis();
    while (true )
    {
      String s= getLineWifi();
      if (s!="")dbg.println(s);
      if (s.startsWith("no change")) break;
      if (s.startsWith("OK"))break;
      if (s.startsWith("ready"))break;
      if (s.startsWith("+CIFSR"))break;
      if ((millis() - flag) > timeOut) 
      {
        dbg.println("TIMEOUT");
        conectado=false;
        break;
      }
    }
    dbg.println("..........................");
  }
  return conectado;
}


