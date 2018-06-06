#include <LiquidCrystal.h>
#include <VirtualWire.h>
//do pinu 11 arduino // 17 pin fizyczny atmega 8
//autor Hubert Korgul 2016

LiquidCrystal lcd(10, 9, 5, 4, 3, 2);

void setup() {
  vw_set_ptt_inverted(true);
  vw_setup(2000);

  vw_rx_start();

  lcd.begin(16, 2);
  lcd.print("");
  pinMode(13, OUTPUT);
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(buf, &buflen))
    {
	int i;

        digitalWrite(13, HIGH);
	
	for (i = 0; i < buflen; i++)
	{
	    //Serial.print(buf[i], HEX);
	    lcd.print((char)buf[i]);
            if(i == 15)
              lcd.setCursor(0, 1);
	}
        digitalWrite(13, LOW);
        lcd.setCursor(0, 0);
    }
}

