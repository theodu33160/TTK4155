#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdint.h>
#include <avr/io.h>

void ADC_init();
uint16_t ADC_read();

#endif
