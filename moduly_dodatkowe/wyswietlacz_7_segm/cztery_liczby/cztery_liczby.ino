#define POROWNYWANA 1000
#define START_TIME 65411
//kwarc 8MHz
//przerwania z czestotliwoscia 1000Hz (65411) 250Hz na cyfre
//przerwania z czestotliwoscia 500Hz (65286) 125Hz na cyfre
//przerwania z czestotliwoscia 250Hz (65036) 62.5Hz na cyfre
//przerwania z czestotliwoscia 125Hz (64536) 31.25Hz na cyfre
//przerwania z czestotliwoscia 40Hz (62411) 10Hz na cyfre
//to f/2 dla przebiegu przemiennego
//to f/4 przemiatanie czyli f na cyfre

void setup() {
  DDRB = 255; //wyjscia dla segmentow
  PORTB = 255; //segmety wylaczone
  DDRD = 15; //wyjscia dla cyfr
  PORTD = 15; //cyfry wylaczone
  
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
int sek = 0; //zerowanie co sekunde -> f tykniec

ISR(TIMER1_OVF_vect){
  TCNT1 = START_TIME;
  
  //porownywana wartosc jest rowna czestotliwosci 
  //wystepowania przerwania wyrazonej w Hz
  if(sek++ == POROWNYWANA){
    count(); //odliczanie sekund
    sek = 0;
  }
  show(); //pokazywanie cyfr na wyswietlaczu
}

void loop() {
  
}

void count(){
  j++;
  if(j == 10){
    j = 0; d++;
    if(d == 10){
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
    PORTD &= ~(1<<PD0); //wylacz poprzednia cyfre wyswietlacza
    PORTB = without_dot[t]; //zmien zawartosc dla cyfry
    PORTD |= (1<<PD3); //wlacz odpowiednia cyfre wyswietlacza
  break;
  case 2:
    PORTD &= ~(1<<PD3);
    PORTB = without_dot[s];
    PORTD |= (1<<PD2);
  break;
  case 1:
    PORTD &= ~(1<<PD2);
    PORTB = without_dot[d];
    PORTD |= (1<<PD1); 
  break;
  case 0:
    PORTD &= ~(1<<PD1);
    PORTB = without_dot[j];
    PORTD |= (1<<PD0); 
    nr_cyfry = 4; //zapetlenie cyklu
  break;
  }
}
