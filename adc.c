ISR(INT2_vect)
{
    //read and store the value to sram
    uint8_t res = ext_adc[0];
    ext_ram[adc_measure] = res;

    adc_measure = (adc_measure + 1)%4;
    // start a new adc conversion
    ext_adc[0] = adc_measure+4;
}

uint8_t readADC(uint8_t channel)
{
	volatile char *ext_adc = (char *) 0x1400;
	
	ext_adc[0] = channel;
	_delay_us(500) ;
	uint8_t result = ext_adc[0];
	return result;
}

void initInterrupt()
{
    sei();     // Enable global interrupts by setting global interrupt enable bit in SREG
    
    //probably useless
    GICR=0xc0;   //Enable External Interrupts INT0 and INT1
	MCUCR |=0x09;  //Configure INT0 active low level triggered and INT1 as rising edge
	
    //start the first read of ADC :
    ext_adc[0] = adc_measure+4;
}

