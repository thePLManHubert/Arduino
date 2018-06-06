#define UART_BAUD 9600  
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1)  

void USART_Init( uint16_t ubrr);
void USART_Transmit( uint8_t data );
void USART_Puts(char * s);

void setup(){
  USART_Init(__UBRR);
}

void loop(){
  USART_Puts("\r\nCześć Hubercie!");
  delay(500);
}

void USART_Init( uint16_t ubrr)
{
  /* Set baud rate */
  UBRRH = (uint8_t)(ubrr>>8);
  UBRRL = (uint8_t)ubrr;
  /* Enable receiver and transmitter */
  UCSRB = (1<<RXEN)|(1<<TXEN);
  /* Set frame format: 8data, 1stop bit */
  UCSRC = (1<<URSEL)|(3<<UCSZ0);
}

void USART_Transmit( char data )
{
  /* Wait for empty transmit buffer */
  while ( !( UCSRA & (1<<UDRE)) );
  /* Put data into buffer, sends the data */
  UDR = data;
}

void USART_Puts(char * s){
  while(*s) USART_Transmit(*s++);
}
