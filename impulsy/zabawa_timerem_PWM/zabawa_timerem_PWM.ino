
void setup() {
  DDRB = B11111111;
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1A |= (1<<WGM11) | (1<<COM1A1) | (1<<COM1B1);
  TCCR1B |= (1<<CS10) | (1<<WGM12) | (1<<WGM13);
}

void loop() {
  ICR1 = map(analogRead(A5),0,1023,0,255);
  OCR1A = map(analogRead(A0),0,1023,0,ICR1);
}
