#define N 13

void setup() {
  for(int i = 0; i <= 13; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

int x = 10;
unsigned int licznik = 0;

void loop() {
  while(true)
  {
    digitalWrite(N, LOW);
    delayMicroseconds(x);
    digitalWrite(N, HIGH);
    delayMicroseconds(x);
    
    licznik++;
    if(licznik == 65535)
    {
      licznik = 0;
      x++;
      Serial.println(x);
    }
  }
}
