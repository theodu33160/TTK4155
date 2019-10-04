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
//#include "fonts.h"

void write_c(uint8_t data);
void write_d(uint8_t data);
//void write_char(char* c);
void init_OLED();
void OLED_pos(uint8_t row, uint8_t col);
void write_arrow();
void OLED_clean();
void OLED_set_page(uint8_t page);
void OLED_set_column(uint8_t column);
void OLED_white();
void OLED_black();

void oled_goto_line(line);
void oled_goto_column(column);


#endif
