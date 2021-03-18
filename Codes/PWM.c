#define F_CPU 16000000UL	

#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PIN_LED_RED		PB3

void led_init(void){
	DDRB    |= (1 << PIN_LED_RED);
	PORTB   |= (1 << PIN_LED_RED);
}

void timer2_init()
{
	cli(); //disable all interrupts
	TCCR2B = 0x00;	//Stop
	TCNT2 = 0xFF;	//Counter higher 8-bit value to which OCR5xH value is compared with
	OCR2A = 0xFF;	//Output compare register low value for Red Led
	//  Clear OC4A, OC4B & OC4C on compare match (set output to low level)
	TCCR2A |= (1 << COM2A1);
	TCCR2A &= ~(1 << COM2A0);

	// FAST PWM 8-bit Mode
	TCCR2A |= (1 << WGM20);
	TCCR2A |= (1 << WGM21);
	TCCR2B &= ~(1 << WGM22);
	
	// Set Prescalar to 64
	TCCR2B &= ~((1 << CS21) | (1 << CS20));
	TCCR2B |= (1 << CS22);
	
	sei(); //re-enable interrupts
}

// Function for brightness control
void brightness (unsigned char red_led){
	OCR2A = (unsigned char)red_led; 	// active low thats why subtracting by 255
}

void init_devices (void)
{
	led_init();
	timer2_init();
}

//Main Function
int main(void)
{
	init_devices();
	
	while(1)
	{
		for (int i=0; i<256 ;i++)
		{
			brightness(i);
			_delay_ms(10);
		}
	}
	
	return 0;
}