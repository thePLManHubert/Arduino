#include <extEEPROM.h>
//#include <Streaming.h>
#include <Wire.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(10,9,5,4,3,2);

extEEPROM eep(kbits_4, 1, 8); //rozmiar pamięci, liczba kości, wielkość strony

const int TOGGLE = 13;
int address = 0;

void setup()
{ 
    eep.begin(); 
    pinMode(TOGGLE, INPUT);
    lcd.begin(16,2);
}

boolean state = true;

void loop()
{
    
  if(digitalRead(TOGGLE) == HIGH){
    delay(20);
    if(digitalRead(TOGGLE) == HIGH){
      if(state == true){
        lcd.clear();
        address++;
        state = false;
      }
    }
  }
  else
    state = true;
  
  lcd.setCursor(0,0);
  int data = eep.read(address);
  lcd.print(address, HEX);
  lcd.print(": ");
  lcd.print(data, HEX);
   
}
