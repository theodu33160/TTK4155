#include "adc.h"


volatile uint8_t adc_measure = 0;


//volatile uint8_t* ext_ram = (uint8_t) 0x800;
//volatile uint8_t* ext_adc = (uint8_t) 0x1400;


void initInterrupt()
{
    //probably useless
    GICR=0x80;   //Enable External Interrupts INT0 and INT1
    //MCUCR |=0x09;  //Configure INT0 active low level triggered and INT1 as rising edge
    MCUCR |= 1 << ISC11; //Configure INT0 active low level triggered and INT1 as rising edge
    MCUCR |= 1 << ISC10; //Configure INT0 active low level triggered and INT1 as rising edge
    
    sei();     // Enable global interrupts by setting global interrupt enable bit in SREG

    //start the first read of ADC :
//    readADC(0x4); // to init the interrupt
printf("init interrupt finished");
}


ISR(INT1_vect)
{
    //read and store the value to sram
    uint8_t res = ext_adc[0];
    //2 steps because the same wires
    ext_ram[adc_measure] = res;

    adc_measure = (adc_measure + 1)%4;
    // start a new adc conversion
    ext_adc[0] = (char) adc_measure+4;
    printf("interrupt finished");
}


/*
uint8_t readADC2(uint8_t channel)
{
	volatile char *ext_adc = (char *) 0x1400;

	ext_adc[0] = channel;
	_delay_us(500) ;
	uint8_t result = ext_adc[0];
	return result;
}


