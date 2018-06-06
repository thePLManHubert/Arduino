#define START_TIME 65535

void setup() {
  DDRB = B11111111;
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<<CS11) | (1<<CS10); //prescaler 64
  TIMSK |= (1<<TOIE1); //przerwania timera wlaczone
  
  TCNT1 = START_TIME;
  PORTB = B00001000;
}

ISR(TIMER1_OVF_vect){
  TCNT1 = START_TIME;
  PORTB ^= B00011000;
}

void loop() {
  
}
