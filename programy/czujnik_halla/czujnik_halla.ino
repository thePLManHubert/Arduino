void setup() {
  pinMode(8, INPUT);

}

bool currState = HIGH;
bool prevState;
int licznik = 0; 
void loop() {
  prevState = currState;
  currState = digitalRead(8);
  if(!currState && (prevState != currState))
  {
    licznik = licznik + 1;
    Serial.println(licznik);
  }
}
