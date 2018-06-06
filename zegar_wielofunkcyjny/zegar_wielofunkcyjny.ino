#include <OneWire.h>
#include <DallasTemperature.h>

#define POROWNYWANA 400
//porownywana wartosc jest rowna czestotliwosci 
//wystepowania przerwania wyrazonej w Hz

#define START_TIME 65376
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

#define DATA_SWITCH (1<<PB2)
#define HOUR (1<<PB3)
#define MINUTE (1<<PB4)
// definicje danych stanu

#define ONE_WIRE_BUS 13 //PB5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;
//dane dla termometru


void setup() {
  sensors.begin();
  sensors.getAddress(insideThermometer, 0);
  sensors.setResolution(insideThermometer, 9);
  
  DDRD = 255; //wyjscia dla segmentow
  PORTD = 255; //segmety wylaczone
  DDRB = 3; //wyjscia dla cyfr
  PORTB = 3; //cyfry wylaczone
  PORTB |= (7<<2); //input pullup
  
  TCCR1A = 0;
  TCCR1B = 0;
  
  TCCR1B |= (1<<CS11) | (1<<CS10); //prescaler 64
  TIMSK |= (1<<TOIE1); //przerwania zegara
  
  TCNT1 = START_TIME;
}



/*-------------------------------------------------
* Zmienne globalne i potrzebne tablice: 
* 1. Tablica znaków bez kropki dziesiętnej.
* 2. Tablica znaków z kropką dziesiętną.
* 3. Zmienne dekad dziesiątek i jedności dla
*    godzin, minut i sekund.
* 4. Tablica danych do wypisania na wyświetlaczu.
* 5. Zmienna dla temperatury.
* 6. Zmienna zliczająca upływające milisekundy.
* 7. Zmienna zliczająca upływające sekundy.
*    (7. i 8. są na użytek mikrokontrolera)
* 8. Zmienna zawierająca stan czyli wskazująca 
*    na to jakie dane są obecnie wyświetlane.
*-------------------------------------------------*/

/*1*/ uint8_t without_dot[13] = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144, 191, 198, 255};
/*2*/ uint8_t with_dot[13] = {64, 121, 36, 48, 25, 18, 2, 120, 0, 16, 63, 70, 127};
/*3*/ uint8_t hd = 0, hj = 0, md = 0, mj = 0, sd = 0, sj = 0; //
/*4*/ uint8_t tab[4] = {255, 255, 255, 255};
/*5*/ int8_t temp;
/*6*/ uint16_t msec = 0; //zerowanie co sekunde -> f tykniec
/*7*/ uint8_t sec = 0;
/*8*/ uint8_t state = 0; //0 = godziny + minuty
                         //1 = minuty + sekundy
                         //2 = temperatura



/*-------------------------------------------------
* Przerwanie timera: wywołuje funkcję odliczania 
* czasu, ustawia stan zadany przez użytkownika,  
* zeruje timer i czuwa nad wyświetlaniem danych 
* na wyświetlaczu siedmiosegmentowym
*-------------------------------------------------*/

ISR(TIMER1_OVF_vect){
  TCNT1 = START_TIME;
  
  if(msec++ == POROWNYWANA){
    msec = 0; //zerowanie zmiennej 
    count(); sec++;//odliczanie czasu
    if(sec == 5){ //sprawdzanie temperatury co 5 sekund
      sec = 0;
      get_temp();
    }
  }
  //ustawia odpowiednie dane do wyświetlania (stan)
  switch(state){
    case 0: go_h_min();
    break;
    case 1: go_min_sec();
    break;
    case 2: go_temperature(temp);
    break;
  }
  show(); //pokazywanie cyfr na wyswietlaczu
}



/*-------------------------------------------------
* Funkcja odmierzająca czas. Działa niezależnie od 
* aktualnego stanu. Wywoływana co sekundę przez
* przerwanie timera.
*-------------------------------------------------*/

void count(){
  sj++;
  if(sj == 10){
    sj = 0; sd++;
    if(sd == 6){
      sd = 0; mj++;
      if(mj == 10){
        mj = 0; md++;
        if(md == 6){
          md = 0; hj++;
          if(hj == 10){
            hj = 0; hd++;            
          }
          if(hd == 2 && hj == 4){
            hd = hj = 0;
          }
        }
      }
    }
  }
}



/*-------------------------------------------------
* Ustawia liczbę minut na zegarku - inkrementując 
* zmienne minutowe przy wywołaniu. Zajmuje się 
* też zerowaniem zmiennych sekundowych. MAX_MIN = 59
*-------------------------------------------------*/

void set_minutes(){
  mj++; sd = sj = 0;
  if(mj == 10){
    mj = 0; md++;
    if(md == 6){
      md = 0; 
    }
  }
}



/*-------------------------------------------------
* Ustawia liczbę godzin na zegarku - inkrementując 
* zmienne godzinowe przy wywołaniu. MAX_H = 23
*-------------------------------------------------*/

void set_hours(){
  hj++;
  if(hj == 10){
    hj = 0; hd++;
  }
  if(hd == 2 && hj == 4){
      hd = hj = 0; 
  }
}



/*-------------------------------------------------
* Przypisuje odpowiednie dane do tablicy "tab" 
* celem pokazania ich na wyśwetlaczu.
* Te dane to godziny, kropka oddzielająca godziny 
* od minut i minuty.
*-------------------------------------------------*/

void go_h_min(){
  
  tab[3] = without_dot[hd];
  if(msec < POROWNYWANA/2) tab[2] = with_dot[hj];
  else           tab[2] = without_dot[hj];
  tab[1] = without_dot[md];
  tab[0] = without_dot[mj];
}



/*-------------------------------------------------
* Przypisuje odpowiednie dane do tablicy "tab" 
* celem pokazania ich na wyśwetlaczu.
* Te dane to minuty, kropka oddzielająca minuty 
* od sekund i sekundy.
*-------------------------------------------------*/

void go_min_sec(){
  tab[3] = without_dot[md];
  if(msec < POROWNYWANA/2) tab[2] = with_dot[mj];
  else           tab[2] = without_dot[mj];
  tab[1] = without_dot[sd];
  tab[0] = without_dot[sj];
}



/*-------------------------------------------------
* Przypisuje odpowiednie dane do tablicy "tab" 
* celem pokazania ich na wyśwetlaczu.
* Te dane to temperatura w stopniach Celsjusza.
*-------------------------------------------------*/

void go_temperature(int8_t x){
  signed high, low;
  
  high = x / 10;
  low = x % 10;
  
  if(temp < 0 && temp > -100) {
    tab[3] = without_dot[10];
    tab[2] = without_dot[12];
    if(x < -9)
      tab[2] = without_dot[-high];
    tab[1] = without_dot[-low];
  }
  else if (temp >= 0 && temp < 100){
    tab[3] = without_dot[12];
    tab[2] = without_dot[12];
    if(x > 9)
      tab[2] = without_dot[high];
    tab[1] = without_dot[low];
  }
  tab[0] = without_dot[11];
}



/*-------------------------------------------------
* Nie zaimplementowane ***
*-------------------------------------------------*/

void get_temp(){
  sensors.requestTemperatures();
  temp = sensors.getTempC(insideThermometer);
}


/*-------------------------------------------------
* Funkcja wyswietlająca dany zestaw czterech
* cyfr na kolejnych pozycjach wyświetlacza 
* począwszy od lewej strony.
*
* dn = digit, od najbardziej znaczącej
* do najmniej znaczącej 3,2,1,0
*
*       zmienne globalne na potrzeby funkcji      */
  uint8_t nr_cyfry = 4;
/*------------------------------------------------*/

void show(){ 
  nr_cyfry--; //przejdz do nizszej cyfry
  
  switch(nr_cyfry){
  case 3:
    PORTD = tab[3]; //zmien zawartosc dla cyfry
    PORTB ^= (B10<<PB0); //przelacz odpowiednia cyfre wyswietlacza
  break;
  case 2:
    PORTD = tab[2];
    PORTB ^= (B01<<PB0);
  break;
  case 1:
    PORTD = tab[1];
    PORTB ^= (B10<<PB0);
  break;
  case 0:
    PORTD = tab[0];
    PORTB ^= (B01<<PB0);
    nr_cyfry = 4; //zapetlenie cyklu
  break;
  }
}



/*-------------------------------------------------
* Funkcja główna programu. Odpowiada za przechwyt 
* informacji o stanie przycisków funkcyjnych zegara.
*
*       zmienne globalne na potrzeby funkcji      */
  boolean pressed = false;
/*------------------------------------------------*/

void loop() {
  if(!(PINB & DATA_SWITCH) || !(PINB & HOUR) || !(PINB & MINUTE)){
    if(!pressed){
      if(!(PINB & DATA_SWITCH)){
        state = (state + 1) % 3;
        pressed = true;
      }
      if(!(PINB & HOUR)){
        set_hours();
        pressed = true;
      }
      if(!(PINB & MINUTE)){
        set_minutes();
        pressed = true;
      }
    }
  }
  else pressed = false;
}
