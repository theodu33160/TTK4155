#include "oled.h"
#include "fonts.h"

#define ADRESSING_MODE_HORIZONTAL 0x00 // HORIZONTAL
#define ADRESSING_MODE_PAGE 0x02 //  PAGE
volatile uint8_t col=0;
volatile uint8_t page=0;


void write_c(uint8_t data){
	char *ext_mem=(char*)0x1000;
	ext_mem[0]=data;
}

void write_d(uint8_t data){
	char *ext_mem=(char*)0x1200;
	ext_mem[0]=data;
}


/*void OLED_init(){
	write_c(0xae);        //  display  off
	write_c(0xa1);        //segment  remap
	write_c(0xda);        //common  pads  hardware:  alternative
	write_c(0x12);
	write_c(0xc8);        //common  output scan direction:com63~com0
	write_c(0xa8);        //multiplex  ration  mode:63
	write_c(0x3f);
	write_c(0xd5);        //display  divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81);        //contrast  control
	write_c(0x50);
	write_c(0xd9);        //set  pre-charge  period
	OLED_Mode(ADRESSING_MODE_PAGE);
//	write_c(0x21);
//	write_c(0x20);        //Set  Memory  Addressing  Mode
	write_c(0x02);
	write_c(0xdb);        //VCOM  deselect  level  mode
	write_c(0x30);
	write_c(0xad);        //master  configuration
	write_c(0x00);
	write_c(0xa4);        // A4 : out  follows  RAM  content
	write_c(0xa6);        //set  normal  display
	write_c(0xaf);        //  display  on
	//write_c(0xb0);
	//write_c(0xB0);
	//write_c(0x00);
//	write_c(0x10);
	OLED_black();		//set display full black
	OLED_home();
	_delay_ms(500);
	printf("OLED_init done");
}*/
void oled_init()
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
}

void OLED_white()
{
	for (uint8_t i = 0; i<8; i++){
		for (uint8_t j = 0 ; j<128; j++){
			OLED_pos(i,j);
			write_d(0xFF);
		}
		printf(" done\n");
	}
	//write_c(0xA5);
}

void OLED_black()
{

	OLED_home();
	for (uint8_t i = 0; i<8; i++){
		for (uint8_t j = 0 ; j<128; j++){
			OLED_pos(i,j);
			write_d(0x00);
		}
	}
}

void write_char(char c)
{

printf("line 0 = %d,\n\r col= %d\n\r",page, col);

	for (uint8_t i =0 ; i<8 ; i++)
	{

		write_d(pgm_read_word(&font8[c-32][i])); //shift linked to ASCII table
		colInc();
		OLED_pos(page,col);
		_delay_ms(100);

	}
}

void OLED_printf(const char *data)
{

	while (*data != '\0')
	  write_char(*data++);
}
void OLED_home() //set the cursor to position 0,0
{
	OLED_pos(0,0);
/*	write_d(0x01);
	write_d(0x03);
	write_d(0x05);*/
	//OLED_pos(0,0);
}

void OLED_Mode(char mode)
{
	write_c(0x20); //horizontale
	write_c(mode);
}



void OLED_goto_line(uint8_t line)
{
	if (line < 0 || line > 7)
		return 0;
	else{
		write_c(0xB0 + line);
		//printf("%d\n\r", line);
	}
}

void OLED_goto_column(uint8_t column)
{
	if (column < 0 || column > 128)
		return 0;
	else{
		uint8_t colLow = column % 16;
		uint8_t colHigh = column / 16;

		write_c(colLow); //0x00 + (column&0x0F));
		write_c(16+colHigh); //0x10 + ((column&0xF0)>>4));


	}
}

void OLED_pos(uint8_t page,uint8_t col)
{

	OLED_goto_line(page);
	OLED_goto_column(col);
}

void colInc()
{
	if(col>127){
		page++;
		col =0;

	}
	else
	{
		col+=1;

	}
	if (page ==8) page =0;
}
