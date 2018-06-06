#include <Wire.h>
#include <Eeprom24C01_02.h>
#include <LiquidCrystal.h>

#define EEPROM_ADDRESS  0x50

LiquidCrystal lcd(10,9,5,4,3,2);
static Eeprom24C01_02 eeprom(EEPROM_ADDRESS);



void setup(){
  lcd.begin(16,2);
  eeprom.initialize();
  
  byte data;
  int8_t ss,s,m,h;
  
  //eeprom.writeByte(0, 0);
  
  //eeprom.writeByte(4, to_BCD(17));
  //eeprom.writeByte(3, to_BCD(1));
  //eeprom.writeByte(2, to_BCD(0));
  
    
  while(1)
  {
    //ss = eeprom.readByte(1);
    s = eeprom.readByte(2);
    m = eeprom.readByte(3);
    h = eeprom.readByte(4);
    
    lcd.setCursor(0,0);
    
    if(h < 10)
      lcd.print(0);
    lcd.print(from_BCD(h));
    lcd.print(":");
    if(m < 10)
      lcd.print(0);
    lcd.print(from_BCD(m));
    lcd.print(":");
    if(s < 10)
      lcd.print(0);
    lcd.print(from_BCD(s));
    //lcd.print(":");
    //lcd.print(from_BCD(ss));
  }
}



/*--------------------------------------------------
*
*
*
*-------------------------------------------------*/

uint8_t to_BCD(uint8_t number){
  uint8_t BCD;
  uint8_t high, low;
  
  high = number / 10;
  low = number % 10;
  
  BCD = (high << 4) + low;
  return BCD;
}



/*--------------------------------------------------
*
*
*
*-------------------------------------------------*/

uint8_t from_BCD(uint8_t number){
  uint8_t num;
  uint8_t high, low;
  
  high = (number >> 4);
  low = number & 0xF;
  
  num = high * 10 + low;
  return num;
}



void loop(){
}
