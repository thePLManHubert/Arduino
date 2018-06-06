#include <VirtualWire.h>
//do pinu 12 arduino // 18 pin fizyczny atmega 8
//autor Hubert Korgul 2016
//poprawki 2017

char* To_Char_Array(long x); // Zwraca tablicę znakow typu char odpowiadajaca argumentowi (inaczej - konwersja z long do String)
int Count_All(char* tab[], int tab_length); // Zlicza i sumuje znaki elementow z wszystkich tablic w arg1
char* Together(char* tab[], int tab_length); // Tworzy jedna tablice zawierajaca wyrazy z wszystkich tablic bedacych w arg1

long x = 0; // Zmienna "inkrementowana" (for fun)

void setup()
{
    vw_set_ptt_inverted(true);
    vw_setup(2000);
}

void loop()
{
    char* a = To_Char_Array(x);
    char* tab[] = {a, " OK"}; // Tablica wielu wyrazow do wyswietlenia razem
    char* t = Together(tab, 2); // arg2 = Liczba elementow tablicy 'tab'
    char* czysc = "                                "; // (32 spacje) Do czyszczenia 32 segmentowego wyswietlacza
    char* msg[] = {t,czysc,"Hubert",czysc}; // Ciag wiadomosci do wyslania (tablic char)
    x++;

    for(int i = 0; i < 4; i++){ // ;i; -> jest rozmiarem tablicy 'msg'
      digitalWrite(13, true); // Zapalanie diody
      
      vw_send((uint8_t *)msg[i], strlen(msg[i]));
      vw_wait_tx();
      
      digitalWrite(13, false); // Gaszenie diody
      if(!(i%2)) // Brak opoznienia podczas "czyszczenia ekranu"
        delay(500); // Miedzy elementami tablicy 'msg'
    }
    //delay(1000); // Po wyslaniu ostatniego elementu z tablicy 'msg'
    // Usuniecia elementow powolanych operatorem 'new'
    delete a;
    delete t;
}




char* To_Char_Array(long x){
  char tab[10];
  int counter = 0;
  char* result;
  
  do
  {
    tab[counter] = x%10;
    counter++;
  }while(x = x/10);
  result = new char[counter+1];
  
  for(int i = 0; i < counter; i++)
  {
    result[counter - 1 - i] = tab[i] + '0';
  }
  result[counter] = '\0';
  return result;
}




int Count_All(char* tab[], int tab_length){
  char* temp;
  int p = 0;
  int counter = 0;
  for(int i = 0; i<tab_length; i++, p = 0){
    temp = tab[i];
    while(temp[p] != '\0'){
      counter++;
      p++;
    }
  }
  return counter;
}




char* Together(char* tab[], int tab_length){
  int size_t = Count_All(tab, tab_length);
  char *current = new char[size_t +1];
  int counter = 0;
  int p = 0;
  char* temp;
  
  for(int i = 0; i<tab_length; i++, p = 0){
    temp = tab[i];
    while(temp[p] != '\0'){
      current[counter] = temp[p];
      p++;
      counter++;
    }
  }
    current[size_t ] = '\0';
    return current;
}
