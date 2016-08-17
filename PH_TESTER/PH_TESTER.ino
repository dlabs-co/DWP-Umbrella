
#define runEvery(t) for (static uint32_t _lasttime;(uint32_t)((uint32_t)millis()- _lasttime) >=(t); _lasttime+=(t))

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  runEvery(5000)
  {
    Serial.println(analogRead(A9));
  }
}
