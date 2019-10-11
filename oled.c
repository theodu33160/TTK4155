#include "oled.h"
#include "fonts.h"

#define ADRESSING_MODE_HORIZONTAL 0x00 // HORIZONTAL
#define ADRESSING_MODE_PAGE 0x02 //  PAGE
volatile uint8_t col=0;
volatile uint8_t page=0;


void write_c(uint8_t data){
	volatile char *ext_mem=(char*)0x1000;
	ext_mem[0]=data;
}

void write_d(uint8_t data){
	volatile char *ext_mem=(char*)0x1200;
	ext_mem[0]=data;
}



void OLED_init()
{
	write_c(0xae);		//display off
	write_c(0xa1);		//segment remap
	write_c(0xda);		//common pads hardware: alternative
	write_c(0x12);
	write_c(0xc8);		//common output scan direction:com63~com0
	write_c(0xa8);		//multiplex ration mode:63
	write_c(0x3f);
	write_c(0xd5);		//display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81);		//contrast control
	write_c(0x50);
	write_c(0xd9);		//set pre-charge period
	write_c(0x21);
	write_c(0x20);		//Set Memory Addressing  Mode
	write_c(0x00);
	write_c(0xdb);		//VCOM deselect level mode
	write_c(0x30);
	write_c(0xad);		//master configuration
	write_c(0x00);
	write_c(0xa4);		//out follows RAM content
	write_c(0xa6);		//set normal display
	write_c(0xaf);		//display on
	OLED_black();
}

void OLED_white()
{
	OLED_home();
	for (int i = 0; i<1024; i++){
			write_d(0xFF);
	}
}

void OLED_black()
{
	OLED_home();
	for (int i = 0; i<1024; i++){
			write_d(0x00);
	}
}

void write_char(char c)
{
	for (uint8_t i =0 ; i<8 ; i++)
	{
		write_d(pgm_read_word(&font8[c-32][i])); //shift linked to ASCII table
	}
}

void OLED_printf(const char *data, uint8_t delay)
{
	while (*data != '\0')
    {
        write_char(*data++);
        _delay_ms(delay);
    }
}


void write_char_inv(char c)
{
	for (uint8_t i =0 ; i<8 ; i++)
	{
		write_d(~pgm_read_word(&font8[c-32][i])); //shift linked to ASCII table
	}
}



void OLED_home() //set the cursor to position 0,0
{
	OLED_pos(0,0);
}

void OLED_Mode(char mode)
{
	write_c(0x20); //horizontale
	write_c(mode);
}



void OLED_goto_line(uint8_t line)
{
	write_c(0x22);
	write_c(line);
	write_c(7);
}

void OLED_goto_column(uint8_t column)
{
	write_c(0x21);
	write_c(column);
	write_c(127);

}

void OLED_pos(uint8_t page,uint8_t col)
{

	OLED_goto_line(page);
	OLED_goto_column(col);
}
