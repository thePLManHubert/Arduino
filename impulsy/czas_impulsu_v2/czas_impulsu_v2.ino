#include <LiquidCrystal.h>
#define IN PB3
#define START_TIME 65411L


LiquidCrystal lcd(10, 9, 5, 4, 3, 2);

void setup() {
  DDRB &= ~(1<<IN);
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = START_TIME;
  TCCR1B |= (1<<CS01) | (1<<CS00); //prescaler 64
  TIMSK |= (1<<TOIE1);
}

long time = 0;

ISR(TIMER1_OVF_vect){
  TCNT1 = START_TIME;
  time++;
}

void loop() {
  time = 0;
  
  if(PINB & (1<<IN)){
    lcd.clear();
    do{
      lcd.setCursor(0, 0);
      lcd.print(time);
    }while(PINB & (1<<IN));
  } 
}

//info 

//aby ustawic kilka bitow mozna zastosowac podany przyklad:
//TCCR1B |= (1<<CS12) | (1<<CS10) | (1<<CS08);
