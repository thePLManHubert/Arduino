#define TOGGLE 4
#define LED 3
//PullDown

void setup() {
  pinMode(TOGGLE, INPUT);
  pinMode(LED, OUTPUT);
}

boolean stan = 1;

void loop() {
  if(digitalRead(TOGGLE) == HIGH){
    delay(20);
    if(digitalRead(TOGGLE) == HIGH){
      if(stan == 1){
        digitalWrite(LED, !digitalRead(LED));
        stan = 0;
      }
    }
  }
  else
    stan = 1;
}
