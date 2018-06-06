#include <Wire.h>
#include <LiquidCrystal.h>

#define ADDRESS 0x50
#define POROWNYWANA 1000
#define START_TIME 1536

LiquidCrystal lcd(10,9,5,4,3,2);



void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  
  TCCR1A = 0;
  TCCR1B = 0;
  
  TCCR1B |= (1<<CS11) | (1<<CS10); //prescaler 64
  TIMSK |= (1<<TOIE1); //przerwania zegara
  
  TCNT1 = START_TIME;
}



ISR(TIMER1_OVF_vect){
  TCNT1 = START_TIME;
  
  Wire.requestFrom(ADDRESS,1);

  lcd.clear();
  lcd.setCursor(0,0);
  
  while(Wire.available()){
    int8_t x = Wire.read();
    lcd.print(x);
  }
}



void loop(){
}
