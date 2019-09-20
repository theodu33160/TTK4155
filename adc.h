#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>


volatile uint8_t adc_measure = 0;
volatile uint8_t* ext_ram = 0x800;
volatile uint8_t* ext_adc = 0x1400;


void initInterrupt();
ISR(INT2_vect);
uint8_t readADC(uint8_t channel);