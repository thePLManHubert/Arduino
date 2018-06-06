#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

#define ONE_WIRE_BUS 6

OneWire oneWire(ONE_WIRE_BUS);
LiquidCrystal lcd(10, 9, 5, 4, 3, 2);
DallasTemperature sensors(&oneWire);

float m;

void setup(void)
{
  lcd.begin(16, 2);
  sensors.begin();
  m = sensors.getTempCByIndex(0);
}


void loop(void)
{ 
  lcd.setCursor(0,0);
  sensors.requestTemperatures();
  float val = sensors.getTempCByIndex(0);
  if(val < m){
    m = val;
  }
  lcd.print(val);
  lcd.print(" st. C");
  delay(2000);
  lcd.clear();
}
