#define TIME_SEC 10L //wartosc long zapobiega przepelnieniu

#define BUTTON 0
#define RED 4
#define BLUE 3
#define YELLOW 2
#define GREEN 1

#define TIME TIME_SEC*1000
#define TIME_BASE 1
#define DIODE_X TIME/TIME_BASE/4
//czas w milisekundach
#define START_TIME 106
//wartosc startowa dla timera


void setup(){
  DDRB = B111110;
  PORTB |= (1<<BUTTON);
  
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = START_TIME;
  TCCR0B |= (1<<CS01) | (1<<CS00); //prescaler 64
  TIMSK0 |= (1<<TOIE0); //przerwania timera wlaczone
}


int counter = 0;
int was_pressed = 0;


ISR(TIM0_OVF_vect){
  TCNT0 = START_TIME; //przerwanie co 1ms
  
  if(!(PINB & (1<<BUTTON))){//przycisk nacisniety
    PORTB |= (1<<RED) | (1<<BLUE) | (1<<YELLOW) | (1<<GREEN); //zapalenie wszystkich diod
    counter = 0; //wyzeruj licznik
    was_pressed = 1; //ustaw flage wlaczenia swiatla
  }
  
  if(was_pressed){
    counter++;
    
    switch(counter){ //wylaczaj kolejne diody
    case (DIODE_X): PORTB &= ~(1<<GREEN); break;
    case (DIODE_X*2): PORTB &= ~(1<<YELLOW); break;
    case (DIODE_X*3): PORTB &= ~(1<<BLUE); break;
    case (DIODE_X*4): PORTB &= ~(1<<RED); 
      was_pressed = 0; //zmien flage
      counter = 0; //wyzeruj licznik
    break;
    }
    
  }
}


void loop(){
  
}
