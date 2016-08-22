/*
 * Funciones adicionales para lcd
 * Depende de FaBoLCD_PCF8574.h
 * 
 * 
 */
 
#include <Arduino.h>
void printState(String msjError)
{
  lastState=msjError;
  uint8_t _x=0;
  uint8_t _X=0;
  uint8_t msjLen = strlen(msjError.c_str()); // convertir a char array
  if (msjLen >= 16) _x=0;  
  if (msjLen%2==0)       // si msj es par 
  {
      _x = (16/2)-(msjLen/2);
      _X =  (16/2)+(msjLen/2);
  }
  else                   // si msj es impar
  {
      _x= (16/2)-((msjLen+1)/2);
      _X =  (16/2)+((msjLen-1)/2);
  }
  lcd.setCursor(_x,1);
  lcd.print(msjError);
  
  for (int i=0;i<_x;i++)
  {
    lcd.setCursor(i,1);
    lcd.print(" ");
  }
  for (int i=_X;i<=16;i++)
  {
    lcd.setCursor(i,1);
    lcd.print(" ");
  }
  
}
void seeHour()
{
    lcd.clear();
    lcd.setCursor(0,0); // (<X>,<Y>)
    lcd.print(strFecha() + "  " + strHora());
    fecha = strFecha();
    hora  =  strHora();
    debug(strFecha() + "  " + strHora(),OK,DEBUG);
    
    printState(lastState);
    //delay(2000);
   //lcd.setCursor(11,0);
   // lcd.print(strHora());
}

void seeBanner()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("DWP Cultivo");
  lcd.setCursor(3,1);
  lcd.print("Hidroponico");
  delay(2000);
  lcd.clear();  
}

void seeBannerDlabs()
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("in cooperation");
  lcd.setCursor(1,1);
  lcd.print("with  Dlabs.co ");
  delay(2000);
  lcd.clear();  
}


