#define DIR_Y 0x7
#define DIR_X 0x6
#define LEFT_SLIDER 0x5
#define RIGHT_SLIDER 0x4

uint8_t readADC(uint8_t direction)
{
	volatile char *ext_adc = (char *) 0x1400;
	
	ext_adc[0] = direction;
	_delay_ms(20) ;
	uint8_t result = ext_adc[0];
	return result;
//	printf("%d\n", result);
}

