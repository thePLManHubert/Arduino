#include <IRremote.h>

int LED = 10;
int RECV_PIN = A5;
boolean LED_VAL = LOW;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  pinMode(LED, OUTPUT);
  irrecv.enableIRIn();
  digitalWrite(LED, LED_VAL);
}

void loop() {
  if (irrecv.decode(&results)) {

    if(results.value == 0xFF00FF)
      LED_VAL = !LED_VAL;
      
    Serial.println(results.value, HEX);
    digitalWrite(LED, LED_VAL);
    irrecv.resume();
  }
}
