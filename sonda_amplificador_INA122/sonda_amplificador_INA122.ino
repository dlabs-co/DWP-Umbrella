#define PIN_SONDA A8

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  //Serial.println(map(analogRead(PIN_SONDA), 377, 429, 0, 100));
  Serial.println("A0 :" +String(analogRead(PIN_SONDA)));
  
  delay(1000);

}
