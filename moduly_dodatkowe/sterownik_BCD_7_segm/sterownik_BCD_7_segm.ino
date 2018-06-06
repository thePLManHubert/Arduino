
void setup() {
  DDRB = 255;
}

byte counter = 0;

void loop() {
  PORTB = counter;
  counter++;
  if(counter == 10)
    counter = 0;
  delay(100);
}
