
void setup() {
  DDRB = B11111111;
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1A |= (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1);
  TCCR1B |= (1<<CS10) | (1<<WGM12);
}

void loop() {
  OCR1A = 255;
}
