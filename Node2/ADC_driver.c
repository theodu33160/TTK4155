#include "ADC_driver.h"
void ADC_init()
{	
	//A is an input (pin of port F)
	DDRF =  0x00; //all analog pins set to INPUT
	// ADC enable
	ADCSRA |= (1<<ADEN);
	// Prescaler 128
	//ADCSRA |= (1<<ADATE);
	ADCSRA |=  (1<<ADPS0) |(1<<ADPS1) | (1<<ADPS2);
	// Voltage reference is AVCC 
	ADMUX |= (1<<REFS0);
	ADMUX |= (1<<REFS1);
	ADC_read();
	
}

uint16_t ADC_read()
{
	uint16_t ADC_data = 0;
	//reading done on ADC number
	ADMUX |= (1<<MUX2);
	//Start conversion
	ADCSRA |= (1<<ADSC);
	// Wait while the conversion is running
	while( ! (ADCSRA && (1<<ADIF)) );
	//if we dont use interrupt clear the ADIF bit zith a 1

	uint8_t data_low = ADCL;
	uint16_t data_high = ADCH;
	//ADCSRA &= ~(1<<ADIF);
	ADC_data = data_low + (data_high<<8);

	return ADC_data;
	
}