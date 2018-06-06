#include <IRremote.h>

IRsend irsend;

void setup()
{
}

void loop() {
	for (int i = 0; i < 1; i++) {
		irsend.sendNEC(0x832201FE, 32);
		delay(40);
	}
	delay(2000); //time delay between each signal burst
}
