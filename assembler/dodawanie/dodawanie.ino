/* Adresy zmiennych nie są znane - obliczane, | 
|  na podstawie odczytu z konsoli:            |
|  ZH = 1;  ZL(x) = adres(x) - 256           */

void add(void);
void store(void);

uint8_t x = 14, y = 10;
uint8_t z = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  Serial.print((int)&x); Serial.print(" (x): ");
  Serial.println(x);
  Serial.print((int)&y); Serial.print(" (y): ");
  Serial.println(y);
  Serial.print((int)&z); Serial.print(" (z): ");
  Serial.println(z);
  add();
  store();
}


void add(void)  {
  asm(
      "ldi r31,1" "\n\t"    // 1. do ZH ładuj 1  
      "ldi r30,21" "\n\t"   // 2. do ZL ładuj 21 -> 277(dec) (zmienna x)
      "ld r2,Z" "\n\t"      // 3. do r2 ładuj wartość spod adresu Z
      "ldi r30,22" "\n\t"   // 4. do ZH ładuj 22 -> 278(dec) (zmienna y)
      "ld r3,Z" "\n\t"      // 5. do r3 ładuj wartość spod adresu Z
      "add r3,r2" "\n\t"    // 6. umieść wynik dodawania r2 i r3 w r3
      "st Z,r3"             // 7. zapisz wartość z r3 pod adres Z (zmienną y)
    );
}

void store(void)  {
  asm(
      "clr r31" "\n\t"      // 1. czyść zawartość ZH (r31)
      "ldi r30,3" "\n\t"    // 2. do ZL ładuj 3 -> 0x0003 (adres rejestru r3)
      "ld r4,Z" "\n\t"      // 3. do r4 ładuj wartość spod adresu Z (spod r3)
      
      "ldi r31,1" "\n\t"    // 4. do ZH ładuj 1 -> 320(dec) (zmienna z)
      "ldi r30,64" "\n\t"   // 5. do ZL ładuj 64
      "inc r4" "\n\t"       // 6. inkrementuj r4
      "st Z,r4"             // 7. zapisz wartość z r4 pod adres Z
    );                      // ostatecznie wartość spod r3 powiększona o 1 
}                           // przechodząc przez r4, ląduje w zmiennej z

