#include "oled2.h"

#include <string.h>
#include "fonts.h"


void oled_init()
{
	oled_write_cmd(0xae);		//display off
	oled_write_cmd(0xa1);		//segment remap
	oled_write_cmd(0xda);		//common pads hardware: alternative
	oled_write_cmd(0x12);
	oled_write_cmd(0xc8);		//common output scan direction:com63~com0
	oled_write_cmd(0xa8);		//multiplex ration mode:63
	oled_write_cmd(0x3f);
	oled_write_cmd(0xd5);		//display divide ratio/osc. freq. mode
	oled_write_cmd(0x80);
	oled_write_cmd(0x81);		//contrast control
	oled_write_cmd(0x50);
	oled_write_cmd(0xd9);		//set pre-charge period
	oled_write_cmd(0x21);
	oled_write_cmd(0x20);		//Set Memory Addressing  Mode
	oled_write_cmd(0x00);
	oled_write_cmd(0xdb);		//VCOM deselect level mode
	oled_write_cmd(0x30);
	oled_write_cmd(0xad);		//master configuration
	oled_write_cmd(0x00);
	oled_write_cmd(0xa4);		//out follows RAM content
	oled_write_cmd(0xa6);		//set normal display
	oled_write_cmd(0xaf);		//display on
}

void oled_write_data(unsigned char ins_d)
{
	volatile char *ext_oled = (char *) OLED_DATA_MEM; // OLED Data
	ext_oled[0] = ins_d;
}

void oled_write_cmd(unsigned char ins_c)
{
	volatile char *ext_oled = (char *) OLED_COMMAND_MEM; // OLED Command
	ext_oled[0] = ins_c;
}

//clear OLED screen
void oled_reset()
{
	oled_goto_line(0);
	oled_goto_column(0);
	for(int i = 0; i < 1024; i++)
	{
		oled_write_data(0x00);
	}
}

//go to specific page of OLED (0 - 7)
void oled_goto_line(uint8_t line)
{
	oled_write_cmd(0x22);
	oled_write_cmd(line);
	oled_write_cmd(7);
}

//go to specific column of OLED (0 - 127)
void oled_goto_column(uint8_t column)
{
	oled_write_cmd(0x21);
	oled_write_cmd(column);
	oled_write_cmd(127);
}

//clear all columns of specific page (0 - 7)
void oled_clear_line(uint8_t line)
{
	oled_goto_line(line);
	for (int i = 0; i < 128; i++)
	{
		oled_write_data(0x00);
	}
}

//go to page and column (0 - 7 | 0 - 127)
void oled_pos(uint8_t row,uint8_t column)
{
	oled_goto_line(row);
	oled_goto_column(column);
}

void oled_print_arrow(uint8_t row, uint8_t col)
{
	oled_pos(row, col);
	oled_write_data(0b00011000);
	oled_write_data(0b00011000);
	oled_write_data(0b01111110);
	oled_write_data(0b00111100);
	oled_write_data(0b00011000);
}

//print a string starting on the current position
//size: 1 - small | 2 - medium | 3 - large
void oled_print(char* name, int size)
{
	for (int i = 0; i < strlen(name); i++)
	{
		oled_print_char(name[i], size);
	}
}

//print a character on the current position
//size: 1 - small | 2 - medium | 3 - large
void oled_print_char(char character, int size)
{
	char mychar;
	int code = ((int) character) - 32;

	if (size == 3)
	{
		for (int k = 0; k < 8; k++)
		{
			mychar =  pgm_read_byte_near(font8[code] + k);
			mychar = mychar;
			oled_write_data(mychar);
		}
	}else if (size == 2)
	{
		for (int k = 0; k < 5; k++)
		{
			mychar =  pgm_read_byte_near(font5[code] + k);
			oled_write_data(mychar);
		}
	}else
	{
		for (int k = 0; k < 4; k++)
		{
			mychar =  pgm_read_byte_near(font4[code] + k);
			oled_write_data(mychar);
		}
	}
}



//write a specific pixel on (x,y)
void oled_write_pixel(int x, int y)
{
	int page = y / 8;
	int page_y = 8 - (y % 8);
	oled_goto_line(page);
	oled_goto_column(x);
	uint8_t data;
	switch (page_y)
	{
		case 1:
		data = 0b10000000;
		break;
		case 2:
		data = 0b01000000;
		break;
		case 3:
		data = 0b00100000;
		break;
		case 4:
		data = 0b00010000;
		break;
		case 5:
		data = 0b00001000;
		break;
		case 6:
		data = 0b00000100;
		break;
		case 7:
		data = 0b00000010;
		break;
		case 8:
		data = 0b00000001;
		break;
	}
	oled_write_data(data);
}
