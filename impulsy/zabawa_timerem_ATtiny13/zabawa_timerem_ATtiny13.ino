#define START_TIME 183 // 1kHz

void setup() {
  sei();
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = START_TIME;
  TCCR0B |= (1<<CS02) | (1<<CS00); //prescaler 64
  TIMSK0 |= (1<<TOIE0);
  DDRB |= 1<<PB3;
}

int i = 0;

ISR(TIM0_OVF_vect){
  TCNT0 = START_TIME;
  if (!(++i %= 124))
    PORTB ^= 1<<PB3;
}

void loop(){}
