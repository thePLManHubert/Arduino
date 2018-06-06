#define MAX_BYTE 255
#define START 4
#define RESET 5
#define DIRECTION 6
#define START_TIME 65411
#define POROWNYWANA 1000
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
  DDRD = 15; //wyjscia dla cyfr + wejscie START i STOP
  PORTD = 112; //cyfry wylaczone + pullup dla START, STOP i DIRECTION
  
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
boolean odliczanie = false;
boolean up = true;
boolean pressed = false;
boolean start_pressed = false;

ISR(TIMER1_OVF_vect){
  TCNT1 = START_TIME;
  
  if(!(PIND & ((1<<START)))){ //przerzutnik T
    if(!start_pressed){
      start_pressed = true;
      odliczanie = !odliczanie;
    }
  }
  else start_pressed = false;
  if(!(PIND & ((1<<RESET)))) j=d=s=t=0;
  if(!(PIND & (1<<DIRECTION))){ //przerzutnik T
    if(!pressed){
      pressed = true;
      up = !up;
    }
  }
  else pressed = false; //koniec prerzutnika RS
  
  if(odliczanie){
    if(up){
      sek++;
      //porownywana wartosc jest rowna czestotliwosci 
      //wystepowania przerwania wyrazonej w Hz
      if(sek >= POROWNYWANA/100.){
        count_up(); //odliczanie w gore
        sek = 0;
      }
    }
    else{
      sek--;
      if(sek <= 0){
        count_down(); //odliczanie w dol
        sek = POROWNYWANA/100.;
      }
    }
  }
  show(); //pokazywanie cyfr na wyswietlaczu
}

void loop() {
  
}

void count_up(){
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

void count_down(){
  j--;
  if(j == MAX_BYTE){
    j = 9; d--;
    if(d == MAX_BYTE){
      d = 9; s--;
      if(s == MAX_BYTE){
        s = 9; t--;
        if(t == MAX_BYTE) t = s = d = j = 9;
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
    PORTB = with_dot[s];
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
