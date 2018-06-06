volatile int a = 0;
 
void setup() {
  Serial.begin(9600);
 
  asm (
    "ldi r24, lo8(32767) \n" //0xff
    "ldi r25, hi8(32767) \n" //0x7f
    "sts (a), r24        \n" //lsb
    "sts (a + 1), r25    \n" //msb
    : : : "r24", "r25"
  );
 
  Serial.print("a = "); Serial.println(a);
}
 
void loop(void) { }
