#define START_TIME 65411L
#define BUTTON PB3
#define OUT PB4
#define LENGTH 25 //czas sygnalu w milisekundach

void setup() {
  DDRB |= (1<<OUT); //OUT jako wyjscie
  PORTB |= (1<<OUT); //standardowo sygnal wysoki
  DDRB &= ~(1<<BUTTON); //BUTTON jako wejscie
  PORTB |= (1<<BUTTON); //pullup
  
  TCCR1A = 0; //konfiguracja timera
  TCCR1B = 0; //konfiguracja timera
  TCNT1 = START_TIME; //ustawienie wartosci poczatkowej w timerze
  TCCR1B |= (1<<CS11) | (1<<CS10); //prescaler 64
  TIMSK |= (1<<TOIE1); //przerwania timera wlaczone
}

long time = 0;
int was_pressed = 0;

ISR(TIMER1_OVF_vect){//przerwanie co 1ms
  TCNT1 = START_TIME;
  
  if(!(PINB & (1<<BUTTON)) && !was_pressed){
    PORTB &= ~(1<<OUT); //podawanie sygnalu niskiego
    was_pressed = 1;
    time = 0;
  }
  
  if(was_pressed){   
    time++;
    if(!(time%(LENGTH+1))){
      PORTB |= (1<<OUT); //wylaczenie sygnalu niskiego
    }
    if(!(time%500)){
      was_pressed = 0;
    }
  }
}

void loop() {
  
}
