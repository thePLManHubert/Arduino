
void setup() {
  DDRB = 255;
  PORTB = 255;
  PORTB &= ~(1<<5);
}

int button = 0;

void loop() {
  button++;
  switch(button){
    case 1: PORTB |= (1<<5); PORTB &= ~(1<<1);
    break;
    case 2: PORTB |= (1<<1); PORTB &= ~(1<<2);
    break;
    case 3: PORTB |= (1<<2); PORTB &= ~(1<<3);
    break;
    case 4: PORTB |= (1<<3); PORTB &= ~(1<<4);
    break;
    case 5: PORTB |= (1<<4); PORTB &= ~(1<<5); button = 0;
    break;
  }
  delay(1000);
}
