//program demonstrating arduino endianness [little endian]
char text[32];
 
void setup() {
  uint16_t n16 = 0x1234;     //declare & initialize 16-bit number
  uint32_t n32 = 0x12345678; //declare & initialize 32-bit number
 
  Serial.begin(9600);
 
  uint8_t* pn16 = (uint8_t *)&n16; //declare uint8_t pointer to 1st byte of 16-bit number
  delay(2000); 
  Serial.println(n16, HEX);
  for (uint8_t i=0; i<2; i++) {
    //iterate through both bytes of n16, noting order of digits
    sprintf(text, "%p: %02x \n", pn16, (uint8_t)*pn16++); 
    Serial.print(text);
  }
  Serial.println();
 
  uint8_t* pn32 = (uint8_t *)&n32; //declare uint8_t pointer to 1st byte of 32-bit number
 
  Serial.println(n32, HEX);
  for (uint8_t i=0; i<4; i++) {
    //iterate through all 4-bytes of n32, noting order of digits
    sprintf(text, "%p: %02x \n", pn32, (uint8_t)*pn32++); 
    Serial.print(text);
  }
 
  Serial.println();
 
}
 
void loop(void) { }
