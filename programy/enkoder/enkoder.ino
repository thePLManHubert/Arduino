void setup() {
  pinMode(2,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7), zlicz, FALLING);
  Serial.begin(9600);
}

int count=0;

void zlicz()
{
  if(digitalRead(2))
  count--;
  else count++;
  Serial.println(count);
}

void loop() {
}
