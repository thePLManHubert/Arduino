#include <IRremote.h>

int RECV_PIN = A5;
IRrecv irrecv(RECV_PIN);
decode_results results;

char left = KEY_LEFT_ARROW;
char right = KEY_RIGHT_ARROW;
char flip = KEY_DOWN_ARROW;

void setup()
{
  Keyboard.begin();
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {

    if(results.value == 0xFF30CF
    || results.value == 0xFF10EF)
      Keyboard.press(left);
    else if(results.value == 0xFF38C7
         || results.value == 0xFFE01F)
      Keyboard.press(right);
    else if (results.value == 0xFF00FF)
      Keyboard.press(flip);
      
    Keyboard.releaseAll();
    irrecv.resume();
  }
}
