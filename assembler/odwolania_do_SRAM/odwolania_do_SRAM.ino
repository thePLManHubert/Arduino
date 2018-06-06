volatile  byte a = 0;
 
void setup() {
  Serial.begin(9600);
 
  asm (
    "ldi r26, 42  \n"  // ładuj 42 do r26
    "sts (a), r26 \n"  // zapisz 42 w zmiennej a; (a) oznacza adres zmiennej a
    : : : "r26"        // lista operandów i używanych rejstrów (opcjonalna)
  );                   // ale lepiej jej używać
}
 
void loop() { 
  delay(1000);
  Serial.print("a = "); Serial.println(a);
}
