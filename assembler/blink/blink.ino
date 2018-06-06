void setup() {
  asm (
  "sbi %0, %1 \n"
    : : "I" (_SFR_IO_ADDR(DDRB)), "I" (DDB3)
  );
}

void loop() {
  asm (
  "in r24, %0  \n"
  "eor r24, %1 \n"
  "out %0, r24 \n"
  : : "I" (_SFR_IO_ADDR(PORTB)), "r" ((uint8_t)_BV(PORTB3)) : "r24"
);
  delay(1000);
}
