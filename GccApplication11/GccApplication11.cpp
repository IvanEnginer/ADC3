#include <avr/io.h>
#include <avr/interrupt.h>

ISR(ADC_vect)
{
	unsigned int ADCdata;
	ADCdata = ADCW;	
	if (ADCdata > (2046 / 5))
	{
		PORTB = 0xFF;
	} 
	else
	{
		if (ADCdata < (1023 / 5))
		{
			PORTB = 0x01;
		} 
		else
		{
			PORTB =0x00;
		}
	}
	ADCSRA |= 1<<ADSC;
}

int main(void)

{
	DDRB = 0xFF;
	
	ADCSRA |= (1 << ADEN)|(1 << ADSC)|(1 << ADPS2)|(1 << ADPS1)|(0 << ADPS0)|(1 << ADIE);
	
	ADMUX |= (1 << REFS1)|(1 << REFS0)|(0 << MUX4)|(0 << MUX3)|(0 << MUX2)|(0 << MUX1)|(0 << MUX0);
	
	sei();
	
	ADCSRA |= 1<<ADSC;
	
	while(1);
}