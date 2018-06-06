#define START_TIME 65286L

void setup() {
  Serial.begin(9600);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = START_TIME;
  TCCR1B |= (1<<CS11) | (1<<CS10); //prescaler 64
  TIMSK1 |= (1<<TOIE1);
}

ISR(TIMER1_OVF_vect){
  TCNT1 = START_TIME; // ta operacja wykonuje się chyba 2 takty
  Serial.println(millis()); //odlicza pojedyncze milisekundy
}

void loop() {
  
}

//info 

//aby ustawic kilka bitow mozna zastosowac podany przyklad:
//TCCR1B |= (1<<CS12) | (1<<CS10) | (1<<CS08);
