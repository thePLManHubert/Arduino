#define SET 4
#define RESET 5
#define LED 3

void setup() {
  DDRD = B11001111;
  PORTD = B11000111;
}

void loop() {
  if(PIND &(1<<SET)) PORTD |= (1<<LED); // ustawianie bitu LED
  if(PIND &(1<<RESET)) PORTD &= !(1<<LED); // kasowanie bitu LED
}

//info
//
//COS |= (1<<BIT) ustawia bit o numerze BIT w rejestrze COS
//COS &= ~(1<<BIT) kasuje bit o numerze BIT w rejestrze COS
//COS ^= (1<<BIT) zmienia bit o nr BIT w rej COS na przeciwny

//XOR z jedynka zmienia wartosc bitow, XOR z zerem nie zmienia
//gdy zamiast znaku &= jest samo & to zawartosc rejestru nie zmienia sie
//jest to przydatne do pisania warunków
//poniewaz w warunkach zazwyczaj mamy wartosc boolowska, to jest
//tam uzywany przewaznie tylko jeden bit (nie uzywa sie wyrazen typu (COS & B01010000))
//bo nie jest to rowne (COS $(1<<6) && COS &(1<<4)), jest to alternatywa ||
//czyli (COS $(1<<6) || COS &(1<<4)) co moze byc mylace

//zapis COS |= (2<<3) przesunie o trzy bity w lewo wartosc liczby
//2 zapisanej binarnie tj. jeżeli COS == 0 to COS |= (2<<3) == B10000 == 16

//aby ustawic kilka bitow mozna zastosowac podany przyklad:
//COS |= (1<<BIT1) | (1<<BIT2) | (1<<BIT3);
