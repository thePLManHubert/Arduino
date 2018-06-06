#include <LiquidCrystal.h>

#define trig 11
#define echo 12

LiquidCrystal lcd(10, 9, 5, 4, 3, 2);

void setup() {
  lcd.begin(16,2);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop () {
  int czas, dist;
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);
  czas = pulseIn(echo, HIGH);
  dist = (czas/2) / 29.1;
  lcd.setCursor(0,0);
  if(!(millis()%250))
    lcd.clear();
  lcd.print("distance: ");
  lcd.print(dist);
}

