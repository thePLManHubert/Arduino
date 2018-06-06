#include <Keeloq.h>
#include <LiquidCrystal.h>
#include <stdlib.h>

LiquidCrystal lcd(10,9,5,4,3,2);

void setup()
{
  lcd.begin(16, 2);
}

int i = 0;
int j = 0;

void loop()
{
  Keeloq k(0x01020304+i,0x05060708+j);
  
  unsigned long enc = k.encrypt(6623281UL);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("After encrypt: ");
  lcd.setCursor(0, 1);
  char buffer[16];
  char * liczba = ultoa(enc, buffer, 10);
  lcd.print(liczba);
  
  unsigned long dec = k.decrypt(enc);
  
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  
  lcd.print("After decrypt: ");
  lcd.setCursor(0, 1);
  
  liczba = ultoa(dec, buffer, 10);
  lcd.print(liczba);
  
  i += 13;
  j += 2*i + 3;
  
  delay(5000);
}
