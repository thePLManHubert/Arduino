volatile byte a = 10;
volatile byte b = 20;

void setup() {
  Serial.begin(9600);
  char text[32];
  delay(2000);
  
  sprintf(text, "a = %d, b = %d", a, b);
  Serial.println(text);
  
  swap1();
  
  sprintf(text, "a = %d, b = %d", a, b);
  Serial.println(text);
  
  swap2();
  
  sprintf(text, "a = %d, b = %d", a, b);
  Serial.println(text);
}

void loop() {
  
}


void swap1() {
    byte c = a; 
    a = b; 
    b = c;
}


void swap2() {
  asm (
    "lds r24, (a) \n"
    "lds r26, (b) \n"
    "sts (b), r24 \n" //exchange registers
    "sts (a), r26 \n"
    : : : "r24", "r26"
  );
}
