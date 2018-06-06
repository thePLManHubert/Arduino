
void setup() {
  DDRB = 255;
}

void loop() {
  int value = analogRead(A0);
  float voltage = value * (5.0 / 1023.0);
  int button;
  
  if(voltage > 0.3 && voltage < 0.6) button = 1;
  else if(voltage > 0 && voltage < 0.06) button = 2;
  else if(voltage > 0.7 && voltage < 0.95) button = 3;
  else if(voltage > 1.1 && voltage < 1.3) button = 4;
  else if(voltage > 1.5 && voltage < 1.8) button = 5;
  else if(voltage > 2 && voltage < 2.2) button = 6;
  else if(voltage > 2.4 && voltage < 2.7) button = 7;
  
  switch(button){
    case 1: PORTB |= (1<<1);
    break;
    case 2: PORTB |= (2<<1);
    break;
    case 3: PORTB |= (3<<1);
    break;
    case 4: PORTB |= (4<<1);
    break;
    case 5: PORTB |= (5<<1);
    break;
    case 6: PORTB |= (6<<1);
    break;
    case 7: PORTB |= (7<<1);
    break;
    default: PORTB = 0;
  }
}
