//def Usart
#define F_CPU 2000000UL // Controller operating frequency
#define BAUD 4800 // Communication speed
#define UBRRL_value 25//(F_CPU/(BAUD*16))-1 // According to the given speed, calculate the value for the register UBRR

//def spi
#define SS 2
#define MOSI 3
#define MISO 4
#define SCK 5

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

//USART functions:
void init_USART() {
	UBRRL = UBRRL_value;       //Lowest 8 bits UBRRL_value
	UBRRH = UBRRL_value >> 8;  //Highest 8 bits UBRRL_value
	UCSRB |=(1<<TXEN);         //Transmit enable bit
	//
	UCSRB |=(1<<RXEN);		   //Receive enable bit
	//
	UCSRC |=(1<< URSEL)|(1<< UCSZ0)|(1<< UCSZ1); //Set the format to 8 data bits
	UCSRA |=(0 << U2X);
}

void send_UART(char value) {
	while(!( UCSRA & (1 << UDRE)));   // Waiting for the transfer buffer to clear
	UDR = value; // put the data in the buffer, start the transfer
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}

void spi_init(void) 
{
	DDRB = (1 << MOSI) | (1 << SS) | (1<<SCK);
	SPCR = (1<<SPE) | (1<< MSTR) | (1<<SPR0);
}

void spi_send_data(char spi_data) 
{
	SPDR = spi_data;
	while(!(SPSR & (1<<SPIF)));
}

int main(void)
{
	
	spi_init();
	init_USART();    // init USART  4800/8-N-1
	spi_send_data(0x03);
	spi_send_data(0x03);
	char data;
	while (1)
	{		
		data = USART_Receive();
		spi_send_data(data);		
	}
	
	
	
	
	
}