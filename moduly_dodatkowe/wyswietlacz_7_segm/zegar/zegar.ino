#define POROWNYWANA 250
#define START_TIME 65280
//kwarc 4.096MHz
//przerwania z czestotliwoscia 1000Hz (65472) 250Hz na cyfre
//przerwania z czestotliwoscia 500Hz  (65408) 125Hz na cyfre
//przerwania z czestotliwoscia 250Hz  (65280) 62.5Hz na cyfre
//przerwania z czestotliwoscia 125Hz  (65024) 31.25Hz na cyfre
//przerwania z czestotliwoscia 40Hz   (63936) 10Hz na cyfre
//to f/2 dla przebiegu przemiennego
//to f/4 przemiatanie czyli f na cyfre

void setup() {
  DDRD = 255; //wyjscia dla segmentow PD0 = a, PD1 = b, itd.
  PORTD = 255; //segmety wylaczone
  DDRB = 15; //wyjscia dla cyfr PB0 = j, PB1 = s, itd.
  PORTB = 15; //cyfry wylaczone
  
  TCCR1A = 0;
  TCCR1B = 0;
  
  TCCR1B |= (1<<CS11) | (1<<CS10); //prescaler 64
  TIMSK |= (1<<TOIE1); //przerwania zegara
  
  TCNT1 = START_TIME;
}

byte without_dot[11] = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144, 255};
byte with_dot[11] = {64, 121, 36, 48, 25, 18, 2, 120, 0, 16, 255};
byte j = 0, d = 0, s = 0, t = 0; //jednosci, dziesiatki, setki, tysiace
byte nr_cyfry = 4;
int f = 0; //zerowanie co sekunde -> f tykniec

ISR(TIMER1_OVF_vect){
  TCNT1 = START_TIME;
  
  //porownywana wartosc jest rowna czestotliwosci 
  //wystepowania przerwania wyrazonej w Hz
  if(f++ == POROWNYWANA){
    count(); //odliczanie sekund
    f = 0;
  }
  show(); //pokazywanie cyfr na wyswietlaczu
}

void loop() {
  
}

void count(){
  j++;
  if(j == 10){
    j = 0; d++;
    if(d == 6){
      d = 0; s++;
      if(s == 10){
        s = 0; t++;
        if(t == 10) t = 0;
      }
    }
  }
}

void show(){
  nr_cyfry--; //przejdz do nizszej cyfry
  
  switch(nr_cyfry){
  case 3:
    PORTB &= ~(1<<PD0); //wylacz poprzednia cyfre wyswietlacza
    PORTD = without_dot[t]; //zmien zawartosc dla cyfry
    PORTB |= (1<<PD3); //wlacz odpowiednia cyfre wyswietlacza
  break;
  case 2:
    PORTB &= ~(1<<PD3);
    PORTD = with_dot[s];
    PORTB |= (1<<PD2);
  break;
  case 1:
    PORTB &= ~(1<<PD2);
    PORTD = without_dot[d];
    PORTB |= (1<<PD1); 
  break;
  case 0:
    PORTB &= ~(1<<PD1);
    PORTD = without_dot[j];
    PORTB |= (1<<PD0); 
    nr_cyfry = 4; //zapetlenie cyklu
  break;
  }
}
