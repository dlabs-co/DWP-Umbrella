
#define runEvery(t) for (static uint32_t _lasttime;(uint32_t)((uint32_t)millis()- _lasttime) >=(t); _lasttime+=(t))
#define getRAW analogRead(A9)

#define x1      4
#define x2     10
#define y1    403
#define y2    476
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  int ph=0;
  int M =0;
  runEvery(5000)
  {
    Serial.println(analogRead(A1)); //A9 en le montaje final
  }

  Serial.println(" calculando PH");
  M= (y2 - y1)/(x2 - x1); //pendiente de la recta
  Serial.print("Pendiente: "); Serial.println(M);
  ph= (((PHraw - y1)/(M))+ x1); // valor de ph
  Serial.print("PH: ");Serial.println(ph);
  delay(2000);
  
}
// valores obtenidos
// PH: 4   ---- 476 ---- 475 ---- 475
// PH: 5,4 ---- 455 ---- 456
// PH: 7   ---- 440 ---- 441 ---- 442
// PH: 8,5 ---- 420 ---- 421
// PH: 10  ---- 403 ---- 403 ---- 403
