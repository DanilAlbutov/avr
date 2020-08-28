#define F_CPU 2000000UL // ������� ������� �����������
#define BAUD 4800 // �������� ������ �������
#define UBRRL_value 25//(F_CPU/(BAUD*16))-1 //��������� �������� �������� ������������ �������� ��� �������� UBRR
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
	UBRRL = UBRRL_value;       //������� 8 ��� UBRRL_value
	UBRRH = UBRRL_value >> 8;  //������� 8 ��� UBRRL_value
	UCSRB |=(1<<TXEN);         //��� ���������� ��������
	//
	UCSRB |=(1<<RXEN);		   //��� ���������� ������
	//
	UCSRC |=(1<< URSEL)|(1<< UCSZ0)|(1<< UCSZ1); //������������ ������ 8 ��� ������
	UCSRA |=(0 << U2X);
}

void send_UART(char value) {
	while(!( UCSRA & (1 << UDRE)));   // ������� ����� ��������� ����� ��������
	UDR = value; // �������� ������ � �����, �������� ��������
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
	init_USART();    // init USART  9600/8-N-1
	spi_send_data(0x03);
	spi_send_data(0x03);
	char data;
	while (1)
	{		
		data = USART_Receive();
		spi_send_data(data);		
	}
	
	
	
	
	
}