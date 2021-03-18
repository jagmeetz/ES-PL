#define F_CPU 16000000UL	

#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PIN_ADC			PC1
#define PIN_LED_RED		PB3

unsigned char ADC_Value;
unsigned char adc_reading;
unsigned int value;

void adc_pin_config (void){
	DDRC &= ~(1 << PIN_ADC); //set PORTC direction as input
	PORTC &= ~(1 << PIN_ADC); //set PORTC pins floating
}

void adc_init(){
	ACSR = (1 << ACD);   	// Analog Comparator Disable; else ADC wont work
	ADMUX = (1 << ADLAR);
	// (turn ADC ON) | (set prescalar to 64 110)
	ADCSRA = ((1 << ADEN) |  (1 << ADPS2 | 1 << ADPS1)) ;
}

unsigned char ADC_Conversion(unsigned char ADC_pin){
	unsigned char digital_converted;
	ADC_pin = ADC_pin & 0b00000111;
	//pin number is extracted from ADC_pin
	ADMUX = 0x20 | ADC_pin;
	//MUX bits are assigned pin number where conversion is to take place
	ADCSRA |= (1 << ADSC);
	//start conversion
	while((ADCSRA & (1 << ADIF) ) == 0);
	//wait till conversion is completed
	digital_converted = ADCH;
	//digital value converted from analog input is stored in digital_converted
	ADCSRA |= (1 << ADIF);
	//ADIF is set when conversion is done, it needs to be cleared for next conversion
	return digital_converted;
}

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
	adc_pin_config();
	adc_init();
	led_init();
	timer2_init();
}

//Main Function
int main(void)
{
	//unsigned int value;
	init_devices();
	
	while(1)
	{

		ADC_Value = ADC_Conversion(1);
		brightness(ADC_Value);
	}
	
	return 0;
}