#define TIME_SEC 60L //wartosc long zapobiega przepelnieniu

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
#define TIME_BASE 25 //im wieksza podstawa czasu tym szybciej program jest wykonywany
#define DIODE_X TIME/TIME_BASE/4
//czas w milisekundach

void setup(){
  DDRB = B11111111;
  PORTB = B00001111; //diody zgaszone
  DDRC = B11111111;
  DDRD = B11111101; //PD1 input
  PORTD |= (1<<BUTTON); //pullup
}

int counter = 0;
int was_pressed = 0;

void loop(){
  delay(TIME_BASE); //podstawa czasowa (nacisniecie przycisku trwa zwykle dluzej)
  
  if(!(PIND & (1<<BUTTON))){//przycisk nacisniety
    PORTB |= (1<<RED) | (1<<BLUE) | (1<<YELLOW) | (1<<GREEN); //zapalenie wszystkich diod
    PORTC |= (1<<LIGHT); //wlaczenie swiatla
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
      PORTC &= ~(1<<LIGHT); //wylacz swiatlo
      was_pressed = 0; //zmien flage
      counter = 0; //wyzeruj licznik
    break;
    }
  }
}
