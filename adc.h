#ifndef ADC_H
#define ADC_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>

#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define EXT_RAM 0x800
#define EXT_ADC 0x1400

void initInterrupt();

//uint8_t readADC2(uint8_t channel);


//ISR(INT1_vect);

#endif
