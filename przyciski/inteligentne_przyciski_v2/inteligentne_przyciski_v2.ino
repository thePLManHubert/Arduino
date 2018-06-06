#define BUTTON1 8
#define BUTTON2 9

void setup() {
  pinMode(BUTTON1, INPUT_PULLUP); // + kondensator 100n
  pinMode(BUTTON2, INPUT_PULLUP); // + kondensator 100n
  Serial.begin(9600);
}

int j,d,s,t; //jednosci, dziesiatki, setki, tysiace
int pomoc1 = 96; //pomaga generowac impulsy
int pomoc2 = 96;
int predkosc1 = 1; //1,2,4,8,16,...,2^n < 100
int predkosc2 = 1;
int count1 = 0; // czuwa nad tempem zmiany predkosci
int count2 = 0;
int MAX_PREDKOSC = 32; // < 100

void loop() {
  
  delay(5); //podstawa czasowa dla wszystkich licznikow to 5ms
  
  if(digitalRead(BUTTON1) == LOW){
    pomoc1 += predkosc1; //zwiekszamy licznik pomoc1
    if(++count1 == 300){//5ms*300 => co 1.5 sekundy zwieksza sie predkosc
      count1 = 0; //jezeli count1 osiagnie zadana wartosc nastapi zwiekszenie predkosci
      if(predkosc1 < MAX_PREDKOSC)//zwiekszenie predkosci jezeli nie perzkacza ona maksymalnej
        predkosc1 *= 2;
    }
    if(pomoc1 >= 100){ //100*5ms = 500ms odstep miedzy impulsami przy wcisnietym przycisku
      zwieksz(); //zwieksza licznik dekadowy
      wypisz();  //wypisuje wskazanie licznika
      pomoc1 = 0;//naliczanie kolejnego czasu odstepu miedzy impulsami (0 - 100)
    }
  }else {
    pomoc1 = 96; //gdy czas naciskania > 20ms [(100-96)*5ms] uklad zareaguje na przycisk
    predkosc1 = 1;//przywraca poczatkowy stan predkosci
    count1 = 0;//licznik zmiany predkosci jest zerowany
  }
  
  if(digitalRead(BUTTON2) == LOW){
    pomoc2 += predkosc2;
    if(++count2 == 300){
      count2 = 0;
      if(predkosc2 < MAX_PREDKOSC)
        predkosc2 *= 2;
    }
    if(pomoc2 >= 100){
      zmniejsz();
      wypisz();
      pomoc2 = 0;
    }
  }else {
    pomoc2 = 96;
    predkosc2 = 1;
    count2 = 0; 
  }
}

void zwieksz(){
  j++;
  if(j == 10){
    j = 0;
    d++;
    if(d == 10){
      d = 0;
      s++;
      if(s == 10){
        s = 0;
        t++;
        if(t == 10) t = 0;
      }
    }
  }
}

void zmniejsz(){
  j--;
  if(j == -1){
    j = 9;
    d--;
    if(d == -1){
      d = 9;
      s--;
      if(s == -1){
        s = 9;
        t--;
        if(t == -1){
          t = s = d = j = 9;
        }
      }
    }
  }
}

void wypisz(){
  Serial.print(t);
  Serial.print(s);
  Serial.print(d);
  Serial.print(j);
  Serial.println();
}
