#include <IRremote.h>

int RECV_PIN = A5; //PC5
IRrecv irrecv(RECV_PIN);
decode_results results;

int ON_OFF = 7; //PD7
int XBS = 0; //PD0
int MEM_PROG = 1; //PD1
int PLAY = 2; //PD2
int STOP = 3; //PD3
int BAND = 4; //PD4
int REV = 5; //PD5
int FWD = 6; //PD6

int TAPE = 0; //PC0
int RADIO = 1; //PC1
int CD = 2; //PC2

int current_state = 1; //TAPE = 0, RADIO = 1, CD = 2

int MUX_A = 0; //PB0
int MUX_B = 1; //PB1

int x = 50;

void setup()
{
  DDRD |= 255;
  DDRB |= (1<<MUX_A) | (MUX_B);
  DDRC |= (1<<TAPE) | (1<<RADIO) | (1<<CD);
  PORTD |= (1<<ON_OFF);
  PORTC &= ~(1<<TAPE) & ~(1<<RADIO) & ~(1<<CD);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    
    switch(results.value){
      /*1 ON_OFF*/ case 0xFF00FF:
      PORTD ^= (1<<ON_OFF);
      if(PIND & (1<<ON_OFF))
        set_state();
      break;
      /*2 PLAY*/ case 0xFF10EF:
      PORTD |= (1<<PLAY); delay(x); PORTD &= ~(1<<PLAY);
      break;
      /*3 SWITCH_FWD*/ case 0xFFA05F:
      current_state = (current_state + 1)%3;
      set_state();
      break;
      /*4 STOP*/ case 0xFFE01F:
      PORTD |= (1<<STOP); delay(x); PORTD &= ~(1<<STOP);
      break;
      /*5 REV*/ case 0xFF30CF:
      PORTD |= (1<<REV); delay(x); PORTD &= ~(1<<REV);
      break;
      /*6 FWD*/ case 0xFF38C7:
      PORTD |= (1<<FWD); delay(x); PORTD &= ~(1<<FWD);
      break;
      /*7 BAND*/ case 0xFF708F:
      PORTD |= (1<<BAND); delay(x); PORTD &= ~(1<<BAND);
      break;
      /*8 SWITCH_REV*/ case 0xFF40BF:
      current_state = (3 + current_state - 1)%3;
      set_state();
      break;
      /*9 MEM_PROG*/ case 0xFF58A7:
      PORTD |= (1<<MEM_PROG); delay(x); PORTD &= ~(1<<MEM_PROG);
      break;
      /*10 XBS*/ case 0xFFC03F:
      PORTD |= (1<<XBS); delay(x); PORTD &= ~(1<<XBS);
      break;
    }

    irrecv.resume();
  }
}

void set_state(){
  if(current_state == 0){
    PORTC &= ~(1<<RADIO);
    PORTC &= ~(1<<CD);
    PORTC |= (1<<TAPE);
  }
  else if(current_state == 1){
    PORTC &= ~(1<<TAPE);
    PORTC &= ~(1<<CD);
    PORTC |= (1<<RADIO);
  }
  else{
    PORTC &= ~(1<<TAPE);
    PORTC &= ~(1<<RADIO);
    PORTC |= (1<<CD);
  }
}
