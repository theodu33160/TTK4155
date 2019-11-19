#include "IR_driver.h"

//Function that initializes the IR system.
void IR_init()
{
	ADC_init();
}

//Function that makes an average of the value from the ADC value
uint16_t IR_average_filter()
{
	uint16_t average_read_ADC = 0;
	for( uint8_t read_counter = 0; read_counter < 4; read_counter ++)
	{
		average_read_ADC = average_read_ADC + ADC_read();
		// Prescaler 128
		uint8_t delay = (128 / F_CPU)*15*1000000;
		_delay_us(delay);
	}
	return average_read_ADC/4;

}
