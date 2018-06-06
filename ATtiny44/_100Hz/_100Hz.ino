#define START_TIME 65497

void setup(){
  sei();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = START_TIME;
  TCCR1B |= (1<<CS12) | (1<<CS10); //prescaler 64
  TIMSK1 |= (1<<TOIE1);
  
  DDRA |= _BV(0) | _BV(1);
  PORTA &= ~_BV(1);
  PORTA |= _BV(0);
}

ISR(TIM1_OVF_vect){
  TCNT1 = START_TIME;
  PORTA ^= 3;
}

void loop(){}
