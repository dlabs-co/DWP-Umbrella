#define PIN_BUZZER 13

// DURATION OF THE NOTES 
#define BPM 120    //  you can change this value changing all the others
#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4 
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4

void setup() 
{ 
  pinMode(PIN_BUZZER,OUTPUT);
  Serial.begin(9600);
  //beep(3);
}

void loop() 
{
  beep(3);
  delay(500);
  tone(PIN_BUZZER,400,500);
  delay(500);
}

void beep(uint8_t totalBeeps)
{
  for (int i = 0;i<totalBeeps;i++)
  {//pin, frecuencia(nota) , duracion)
    tone(PIN_BUZZER,400,100);
    delay(500);
    
  }
}

