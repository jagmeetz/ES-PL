#define F_CPU 16000000UL
#include <xc.h>
#include <util/delay.h>

int main(void)
{	DDRD=0XFF;
	PORTD=0X00;
	
    while(1)
    {
    //PORTD=0X01;
	//_delay_ms(1000);
	//PORTD=0X02;
	//_delay_ms(1000);
	//PORTD=0X04;
	//_delay_ms(1000);
	//PORTD=0X08;
	//_delay_ms(1000);
	//PORTD=0X10;
	//_delay_ms(1000);
	//PORTD=0X20;
	//_delay_ms(1000);
	//PORTD=0x40;
	//_delay_ms(1000);
	//PORTD=0X80;
	//_delay_ms(1000); 
	
	int i =0;
	//for(i=0;i<8;i++)
	//{
		//PORTD = PORTD<<i;
		//_delay_ms(1000); 
	//}
	PORTD=0x01;
	_delay_ms(1000);
	while(PORTD!=0x80)
	{
		
		PORTD = PORTD<<1;
		_delay_ms(1000);
	}
	PORTD=0xFF;
	_delay_ms(1000);
    }
}