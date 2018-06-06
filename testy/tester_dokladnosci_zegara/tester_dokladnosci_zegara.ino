#include <LiquidCrystal.h>

#define POROWNYWANA 1000
//porownywana wartosc jest rowna czestotliwosci 
//wystepowania przerwania wyrazonej w Hz

#define START_TIME 1536
//kwarc 4.096MHz
//przerwania z częstotliwością 16000Hz (65532) 4000Hz na cyfrę
//przerwania z częstotliwością 8000Hz (65528) 2000Hz na cyfrę
//przerwania z częstotliwością 4000Hz (65520) 1000Hz na cyfrę
//przerwania z częstotliwością 1000Hz (65472) 250Hz na cyfrę
//przerwania z częstotliwością 500Hz (65408) 125Hz na cyfrę
//przerwania z częstotliwością 400Hz (65376) 100Hz na cyfrę
//przerwania z częstotliwością 250Hz (65280) 62.5Hz na cyfrę
//przerwania z częstotliwością 125Hz (65024) 31.25Hz na cyfrę
//przerwania z częstotliwością 40Hz (63936) 10Hz na cyfrę
//przerwania z częstotliwością 4Hz (49536) 1Hz na cyfrę
//to f/2 dla przebiegu przemiennego
//to f/4 przemiatanie czyli f na cyfre



LiquidCrystal lcd(10, 9, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  
  TCCR1A = 0;
  TCCR1B = 0;
  
  TCCR1B |= (1<<CS11) | (1<<CS10); //prescaler 64
  TIMSK |= (1<<TOIE1); //przerwania zegara
  
  TCNT1 = START_TIME;
}


uint8_t h = 17, m = 50, s = 0, ts = 0;

ISR(TIMER1_OVF_vect){
  TCNT1 = START_TIME;
  
  count();
  show(); //pokazywanie cyfr na wyswietlaczu
}



void count(){
  s++;
  if(s == 60){
    s = 0; m++;
    if(m == 60){
      m = 0; h++;
      if(h == 24){
        h = 0;
      }
    }
  }
}

void show(){
  lcd.setCursor(0,0);
  if(h < 10)
    lcd.print(0);
  lcd.print(h);
  lcd.print(":");
  if(m < 10)
    lcd.print(0);
  lcd.print(m);
  lcd.print(":");
  if(s < 10)
    lcd.print(0);
  lcd.print(s);
}

void loop(){
}
