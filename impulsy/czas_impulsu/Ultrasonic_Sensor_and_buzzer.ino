
#define trig 2
#define echo 3
int buzz = 9;


void setup() {
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
pinMode(buzz, OUTPUT);
digitalWrite (buzz, LOW);
}

void loop () {
  int czas, dist;
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);
  czas = pulseIn(echo, HIGH);
  dist = (czas/2) / 29.1;
  
  if (dist <=10) {
    tone (buzz, 3000, 100);
    delay(200);
  }
  if (dist <=20 && dist >10) {
tone(buzz, 2000,100);    
delay(400);
  }
  if (dist >=20) { 
tone (buzz, 1000, 100);
    delay(800); 
  }
}
