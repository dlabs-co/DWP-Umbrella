// Se ha cambiado la dirección del I2C a 0x27 está en la librería
// include the library code:
#include <Wire.h>
#include <FaBoLCD_PCF8574.h>

#define PINTEMP A7

// initialize the library
FaBoLCD_PCF8574 lcd;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hola, Dlabs!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print("           ");
  lcd.setCursor(0, 1);
  lcd.print(analogRead(PINTEMP));
  delay(1000);
}

