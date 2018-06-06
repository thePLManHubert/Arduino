volatile byte a = 10;
volatile byte b = 20;

void setup() {
  Serial.begin(9600);
  char text[32];
  delay(2000);
  
  sprintf(text, "a = %d, b = %d", a, b);
  Serial.println(text);
  
  asm (
  "" : "=r" (a), "=r" (b) : "0" (b), "1" (a) 
  );
  
  sprintf(text, "a = %d, b = %d", a, b);
  Serial.println(text);
  
}

void loop() {
  
}
