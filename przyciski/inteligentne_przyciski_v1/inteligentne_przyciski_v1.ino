#define BUTTON1 8
#define BUTTON2 9

void setup() {
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  Serial.begin(9600);
}

int j,d,s,t;
int pomoc1 = 96;
int pomoc2 = 96;

void loop() {
  
  delay(5);
  
  if(digitalRead(BUTTON1) == LOW){
    pomoc1++;
    if(pomoc1 == 100){ //100*5ms = 500ms odstep miedzy impulsami przy wcisnietym przycisku
      zwieksz(); //zwieksza licznik dekadowy
      wypisz();  //wypisuje wskazanie licznika
      pomoc1 = 0;//naliczanie kolejnego czasu odstepu miedzy impulsami
    }
  }else pomoc1 = 96; //gdy czas naciskania > 20ms uklad zareaguje na przycisk
  
  if(digitalRead(BUTTON2) == LOW){
    pomoc2++;
    if(pomoc2 == 100){
      zmniejsz();
      wypisz();
      pomoc2 = 0;
    }
  }else pomoc2 = 96;
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
