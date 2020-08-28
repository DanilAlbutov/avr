
#include <asf.h>
#include <asf.h>
#include <util/delay.h>

#define F_CPU 2000000UL
#define SS 2
#define MOSI 3
#define MISO 4
#define SCK 5


int main (void)
{
	
	DDRC = 0b00000001;
	DDRB= (1<<MISO);
	SPCR = (1<<SPE);
	while(1)
	{
		while(!(SPSR & (1<<SPIF)));
		char data = SPDR;
	
	 
	
		if (data == '1') {
			PORTC = 0b00000001;
		}
		if (data == '0') {
			PORTC = 0b00000000;
		}
	}

	
}
