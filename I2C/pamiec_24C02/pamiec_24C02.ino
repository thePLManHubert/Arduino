#include <Wire.h>
#include <LiquidCrystal.h>
#include <Eeprom24C01_02.h>

#define EEPROM_ADDRESS  0x50

static Eeprom24C01_02 eeprom(EEPROM_ADDRESS);
LiquidCrystal lcd(10,9,5,4,3,2);
const int TOGGLE = 13;
byte address = 0;

void setup()
{ 
    eeprom.initialize();
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
  byte data = eeprom.readByte(address);
  lcd.print(address, HEX);
  lcd.print(": ");
  lcd.print(data, HEX);
   
}
