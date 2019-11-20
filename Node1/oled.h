#ifndef F_CPU
#define F_CPU 4962000
#endif

#ifndef OLED_H
#define OLED_H

#define __DELAY_BACKWARD_COMPATIBLE__
#define ADRESSING_MODE_HORIZONTAL 0x00 // horizontal mode
#define ADRESSING_MODE_PAGE 0x02 // page mode

#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void write_c(uint8_t data);
void write_d(uint8_t data);
void OLED_init();
void OLED_white();
void OLED_black();
void write_char(char c);
void OLED_printf(const char *data);
void OLED_printf_slow(const char *data, const uint16_t delay);
void write_char_inv(char c);
void OLED_home();
void OLED_Mode(char mode);
void OLED_goto_line(uint8_t line);
void OLED_goto_column(uint8_t column);
void OLED_pos(uint8_t page, uint8_t col);

#endif
