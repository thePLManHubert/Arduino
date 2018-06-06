
void setup() {
  DDRB = 255;
  
  PORTB |= (1<<PB1);
}

byte counter = 0;

void loop() {
  PORTB ^= (1<<PB1);
  delayMicroseconds(5);
}
