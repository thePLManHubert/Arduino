#include <VirtualWire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char* To_Char_Array(long x); // Zwraca ciag znakow typu char odpowiadajaca argumentowi
int Count_All(char* tab[], int tab_length); // Zlicza i sumuje znaki elementow z wszystkich tablic w arg1
char* Together(char* tab[], int tab_length); // Tworzy jedna tablice zawierajaca wyrazy z wszystkich tablic bedacych w arg1

void setup()
{
    vw_set_ptt_inverted(true);
    vw_setup(2000);
    sensors.begin();
}

void loop()
{
    sensors.requestTemperatures();
    char* a = To_Char_Array(sensors.getTempCByIndex(0)*10);
    char* tab[] = {a}; // Tablica wielu wyrazow do wyswietlenia razem
    char* t = Together(tab, 1); // arg2 = Liczba elementow tablicy 'tab'
    char* msg[] = {t, "     "}; // Ciag wiadomosci do wyslania (tablic char)

    for(int i = 0; i < 2; i++){ // ;i; -> jest rozmiarem tablicy 'msg'
      digitalWrite(13, true); // Zapalanie diody
      
      vw_send((uint8_t *)msg[i], strlen(msg[i]));
      vw_wait_tx();
      
      digitalWrite(13, false); // Gaszenie diody
      if(!(i%2)) // Brak opoznienia podczas "czyszczenia ekranu"
        delay(5000); // Delay miedzy elementami tablicy 'msg'
    }
    //delay(1000); // Po wyslaniu ostatniego elementu z tablicy 'msg'
    // Usuniecia elementow powolanych operatorem 'new'
    delete a;
    delete t;
}




char* To_Char_Array(long x){
  int t = x;
  char tab[10];
  int counter = 0;
  char* result;
  
  do
  {
    tab[counter] = x%10;
    counter++;
  }while(x = x/10);
  
  result = new char[counter+2];
  for(int i = 0; i < counter-1; i++)
  {
    result[i] = tab[counter-1-i] + '0';
  }
  if(!(t%2)){
    result[counter-1] = '\0';
    result[counter] = '\0';
    result[counter+1] = '\0';
  }
  else
  {
    result[counter-1] = '.';
    result[counter] = '5';
    result[counter+1] = '\0';
  }
  
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
  char *current = new char[size_t + 1];
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
