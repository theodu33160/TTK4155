#ifndef OLED_H
#define OLED_H

#define F_CPU 4962000

#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void write_c(uint8_t data);
void init_OLED();
void OLED_pos(uint8_t row, uint8_t col);
void write_arrow();

#endif
