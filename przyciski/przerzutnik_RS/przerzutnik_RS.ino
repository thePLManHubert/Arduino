#define SET 4
#define RESET 5
#define LED 3
//PullDown

void setup() {
  pinMode(SET, INPUT);
  pinMode(RESET, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  if(digitalRead(SET) == HIGH) digitalWrite(LED, HIGH);
  if(digitalRead(RESET) == HIGH) digitalWrite(LED, LOW);
}
