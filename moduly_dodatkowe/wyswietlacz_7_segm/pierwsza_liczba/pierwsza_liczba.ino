
void setup() {
  DDRB = 255;
  PORTB = 255;
}

int without_dot[11] = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144, 255};
int with_dot[11] = {64, 121, 36, 48, 25, 18, 2, 120, 0, 16, 255};
int counter = 0;

void loop() {
  PORTB = with_dot[counter];

  counter++;
  if(counter == 10)
    counter = 0;
    
  delay(1000);
}
