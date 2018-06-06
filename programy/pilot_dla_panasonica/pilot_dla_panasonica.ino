#include <IRremote.h>

#define FOR 0
#define REV 1
#define BAND 2
#define PLAY 3
#define TUNE 4
#define MEM 5
#define XBS 6
#define RECEIVE 7
#define DIODE 8

boolean LED_VAL = LOW;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  //Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode()
  irrecv.enableIRIn();
  digitalWrite(LED, LED_VAL);
}

void loop() {
  if (irrecv.decode(&results)) {

    switch(results.value){
      case 0xFFA05F:
        digitalWrite(FOR, LOW);
        LED_VAL = HIGH;
        delay(100);
      break;
      
      case 0xFF40BF:
        digitalWrite(REV, LOW);
        LED_VAL = HIGH;
        delay(100);
      break;
      
      case 0xFF38C7:
        digitalWrite(BAND, LOW);
        LED_VAL = HIGH;
        delay(100);
      break;
      
      case 0xFF30CF:
        digitalWrite(PLAY, LOW);
        LED_VAL = HIGH;
        delay(100);
      break;
      
      case 0xFFE01F:
        digitalWrite(TUNE, LOW);
        LED_VAL = HIGH;
        delay(100);
      break;
      
      case 0xFF58A7:
        digitalWrite(MEM, LOW);
        LED_VAL = HIGH;
        delay(100);
      break;
      
      case 0xFFC03F:
        digitalWrite(XBS, LOW);
        LED_VAL = HIGH;
        delay(100);
      break;
      
    }
      
    //Serial.println(results.value, HEX);
    digitalWrite(FOR, HIGH);
    digitalWrite(REV, HIGH);
    digitalWrite(BAND, HIGH);
    digitalWrite(PLAY, HIGH);
    digitalWrite(TUNE, HIGH);
    digitalWrite(MEM, HIGH);
    digitalWrite(XBS, HIGH);
    digitalWrite(LED, LOW);
    irrecv.resume();
  }
}
