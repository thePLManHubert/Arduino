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
  
    // Initialize EEPROM library.
    eeprom.initialize();

    int address;
    
    // Read a byte at address in EEPROM memory.
    for(address = 0; address<256; address++){
      byte data = eeprom.readByte(address);
      lcd.setCursor(0,0);
      lcd.print("address ");
      lcd.print(address);
      lcd.setCursor(0,1);
      lcd.print(data);
      lcd.print(" = ");
      lcd.print((char)data);
      delay(500);
      lcd.clear();
    }
}

/**************************************************************************//**
 * \fn void loop()
 *
 * \brief
 ******************************************************************************/
void loop()
{

}
