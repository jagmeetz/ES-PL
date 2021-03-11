
#define F_CPU 16000000UL
#include <xc.h>
#include <util/delay.h>

int main(void)
{	DDRD = DDRD| (1<<4);
	DDRC= DDRC & ~(1<<5);
	PORTB=0x00;
	
while (1) //initialize while loop
{
	if(PINC & (1<<5)) //if PIN5 of port C is high
	{
		PORTD = PORTD | ( 1<<4) ; //PIN4 of port D is high
	}
	else //otherwise
	{
		PORTD = PORTD &  ~( 1<<4) ; //PIN4 of port D will remain low
	}
} 

}