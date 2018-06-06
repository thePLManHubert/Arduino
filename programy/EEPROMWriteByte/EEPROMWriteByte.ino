#include <LiquidCrystal.h>
#include <Wire.h>
#include <Eeprom24C01_02.h>
#define EEPROM_ADDRESS  0x50

static Eeprom24C01_02 eeprom(EEPROM_ADDRESS);

void setup()
{
   // Initialize lcd
    LiquidCrystal lcd(10,9,5,4,3,2);
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print("Initialization...");
    
    // Initialize EEPROM library.
    eeprom.initialize();
    
    int address;
    
    // Write a byte at address in EEPROM memory.
    for(address = 0; address<256; address++){
      eeprom.writeByte(address, address%26 +65);
      // Write cycle time (tWR). See EEPROM memory datasheet for more details.
      delay(5);
    }
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Memory written ");
}

void loop()
{

}
