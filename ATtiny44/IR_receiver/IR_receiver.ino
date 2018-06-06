#include <IRremote.h>

IRrecv irrecv(10);
decode_results results;

void setup()
{
  DDRA = 0xFF;
  irrecv.enableIRIn();
  PORTA = 0xFF;
}

void loop() {
  if (irrecv.decode(&results)) {

    switch(results.value){
      case 0xFD3AC5:
        PORTA ^= _BV(PA0);
      break;
      
      case 0xFDEA15:
        PORTA ^= _BV(PA1);
      break;
      
      case 0xFDC03F:
        PORTA ^= _BV(PA2);
      break;
      
      case 0xFD40BF:
        PORTA ^= _BV(PA3);
      break;
      
      case 0xFD20DF:
        PORTA ^= _BV(PA4);
      break;
      
      case 0xFDD827:
        PORTA ^= _BV(PA5);
      break;
      
      case 0xFD32CD:
        PORTA ^= _BV(PA6);
      break;
      
      case 0xFD827D:
        PORTA ^= _BV(PA7);
      break;
    }
      
    irrecv.resume();
  }
}
