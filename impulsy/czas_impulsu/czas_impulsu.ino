#include <StopWatch.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 9, 5, 4, 3, 2);
int IN = 11;
StopWatch sw_millis;    // MILLIS (default)

void setup() {
    lcd.begin(16,2);
    Serial.begin(9600);
}


void loop() {
  if(digitalRead(IN)){
    lcd.clear();
    sw_millis.start();
    do{
      lcd.setCursor(0, 0);
      lcd.print(sw_millis.elapsed());
    }while(digitalRead(IN));
  }
  sw_millis.stop();
  sw_millis.reset();
}
