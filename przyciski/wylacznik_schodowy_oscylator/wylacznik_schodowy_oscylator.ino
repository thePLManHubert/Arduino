#define TIME_SEC 15L //wartosc long zapobiega przepelnieniu

#define BUTTON 1
//przycisk na PORTD
#define RED 4
#define BLUE 5
#define YELLOW 6
#define GREEN 7
//diody na PORTB
#define LIGHT 7
//swiatlo na PORTC
#define TIME TIME_SEC*1000
#define TIME_BASE 1
#define DIODE_X TIME/TIME_BASE/4
//czas w milisekundach
#define START_TIME 65286L
//wartosc startowa dla timera

void setup(){
  Serial.begin(9600);
  
  DDRB = B11111111;
  PORTB = B00001111; //diody zgaszone
  DDRC = B11111111;
  DDRD = B11111101; //PD1 input
  PORTD |= (1<<BUTTON); //pullup
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = START_TIME;
  TCCR1B |= (1<<CS11) | (1<<CS10); //prescaler 64
  TIMSK1 |= (1<<TOIE1); //przerwania timera wlaczone
}

int counter = 0;
int was_pressed = 0;
long time = 0;

ISR(TIMER1_OVF_vect){
  TCNT1 = START_TIME; //przerwanie co 1ms
  
  if(!(PIND & (1<<BUTTON))){//przycisk nacisniety
    PORTB |= (1<<RED) | (1<<BLUE) | (1<<YELLOW) | (1<<GREEN); //zapalenie wszystkich diod
    PORTC |= (1<<LIGHT); //wlaczenie swiatla
    time = 0;
    counter = 0; //wyzeruj licznik
    was_pressed = 1; //ustaw flage wlaczenia swiatla
  }
  if(was_pressed){
    counter++; time++;
    switch(counter){ //wylaczaj kolejne diody
    case (DIODE_X): PORTB &= ~(1<<GREEN); 
      Serial.println(time); break; //pokazuje czas wylaczenia 1-szej diody
    case (DIODE_X*2): PORTB &= ~(1<<YELLOW); 
      Serial.println(time); break; //pokazuje czas wylaczenia 2-giej diody
    case (DIODE_X*3): PORTB &= ~(1<<BLUE); 
      Serial.println(time); break; //pokazuje czas wylaczenia 3-ciej diody
    case (DIODE_X*4): PORTB &= ~(1<<RED); 
      PORTC &= ~(1<<LIGHT); //wylacz swiatlo
      was_pressed = 0; //zmien flage
      counter = 0; //wyzeruj licznik
      Serial.println(time); //pokazuje czas wylaczenia 4-tej diody
    break;
    }
  }
}

void loop(){
  
}
