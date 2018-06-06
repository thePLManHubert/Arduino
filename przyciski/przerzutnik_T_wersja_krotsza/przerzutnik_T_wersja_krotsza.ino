#define TOGGLE 4
#define LED 3
//PullDown

void setup() {
  DDRD = B11101111; // ustawia pin D4 jako wejscie, reszta to wyjscia
  PORTD = B11110111;// pin D3 to wyjscie w stanie niskim
  ACSR |= (1<<7); // ustawia najstarszy bit rejestru ACSR
}// ACST MSB to bit przechowujacy informacje czy przycisk podpiety do D4 zostal zwolniony po wcisnieciu (tak - 1, nie - 0)

void loop() {
  if(PIND &(1<<TOGGLE)){// sprawdza czy wystapil sygnal wysoki na pinie D4 (czy wcisnieto przycisk)
    delay(20); // opoznienie (drgajace styki)
    if(PIND &(1<<TOGGLE)){ // warunek sprawdzany ponownie
      if(ACSR &(1<<7)){// sprawdza czy zwolniono przycisk
        PORTD = PIND ^(1<<LED);// zmienia stan pinu D3 na przeciwny
        ACSR &= B01111111; // lub ACSR ^= (1<<7); // informuje, ze przycisk jest wcisniety 1 --> 0
      }
    }
  }
  else
    ACSR |= (1<<7); // przycisk jest zwolniony
}
