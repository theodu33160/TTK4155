#ifndef F_CPU
#define F_CPU 4962000UL
#endif

#ifndef IR_DRIVER_H
#define IR_DRIVER_H

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "ADC_driver.h"

void IR_init();
uint16_t IR_average_filter();

#endif
