
void http(int ch_id, String output)
{
  wifi.print("AT+CIPSEND=" + String(ch_id) + ",");
  wifi.println(output.length());


  if (wifi.find(">"))
  {

    wifi.println(output);
    delay(10);
    while (wifi.available() > 0)
    {
      if (wifi.find("SEND OK"))break;
    }
  }
  else
  {
    dbg.println("no escrito");
  }
}


void webServer(int ch_id)
{
  dbg.println("entrando en servir");
  http(ch_id, "<!DOCTYPE HTML>");
  http(ch_id, "<html>");
  http(ch_id, "<head><meta charset=\"UTF-8\"></head>");
  http(ch_id, "<title>Página de prueba</title>");
  http(ch_id, "<body><h1>Cultivo Hidropónico</h1>");
  http(ch_id, "<p>Colaboración Dlabs</p>");
  http(ch_id, "<p>Temperatura: " +String(temperatura) + "</p>");
  http(ch_id, "<p>Humedad: "  + String(humedad) + "</p>");
  ////////////////////////////////////////////////////////////  
  //CONTROLADOR
///////////////////////////////////////////////////////////////  
  http(ch_id, "</body>");
  http(ch_id, "</html>");
  delay(1);
  wifi.println("AT+CIPCLOSE=" + String(ch_id));
}

/*
float parseSetPoint(String auxBuffer)
{
  String aux;
  aux = auxBuffer.substring(auxBuffer.indexOf("fSetPoint"), auxBuffer.indexOf("HTTP"));
  dbg.println("AUX1:" + String(aux));
  aux = aux.substring(aux.indexOf("=") + 1);
  dbg.println("AUX2:" + String(aux));
  return aux.toFloat();
}
*/
