#include "oled.h"

#define ADRESSING_MODE HORIZONTAL // HORIZONTAL or PAGE


/*void write_char(char* c)
{
	write_c(0x21);
	write_c(0x00);
	write_c(0x7f);
	
	for (uint8_t i =0 ; i<8 ; i++)
	{
		//write_d(font8[c][i]);
	}
}*/

void write_c(uint8_t data){
	char *ext_mem=(char*)0x1000;
	ext_mem[0]=data;
}

void write_d(uint8_t data){
	char *ext_mem=(char*)0x1200;
	ext_mem[0]=data;
}

void OLED_init(){
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
	write_c(0x21);	   
	write_c(0x20);        //Set  Memory  Addressing  Mode
	write_c(0x02); 
	write_c(0xdb);        //VCOM  deselect  level  mode
	write_c(0x30);
	write_c(0xad);        //master  configuration
	write_c(0x00);
	write_c(0xa4);        // A4 : out  follows  RAM  content
	write_c(0xa6);        //set  normal  display
	write_c(0xaf);        //  display  on
	//write_c(0xA5);
	printf("OLED_init done");
}

/*void OLED_reset(){

	//write_c(0xA5);
	for (int i=0;i<8;i++){
		write_c(0b10110000);
		write_d(0x00);
	}
}

void OLED_white()
{
	OLED_reset();
	//test for horizontal mode
	_delay_ms(500);
	for (int i=0;i<8;i++){
		write_c(0b10110000);
		write_d(0x00);
	//write_c(0xA5); // set the oled full white
	}
}
*/
void OLED_black()
{
	for (int i = 0; i<8; i++){
		for (int j = 0 ; j<128; j++){
			oled_goto_line(i);
			oled_goto_column(j);
			write_d(0x00);
		}
	}
}

/*void oled_home(){

	//oled_pos(0,0);
}*/

void oled_goto_line(line)
{
	if (line < 0 || line > 7)
		return 0;
	else{
		write_c(0xB0 + line);
	}
}

void oled_goto_column(column)
{
	if (column < 0 || column > 127)
		return 0;
	else{
		int colLow = column % 16;
		int colHigh = column / 16;

		write_c(0x00 + colLow);
		write_c(0x10 + colHigh);
	}
}


void OLED_clean()
{
	for( int j = 0;j<8;j++)
	{
		for (int i = 0; i<128 ;i++)
		{
			write_d(0b00000000);
			//OLED_pos(j,i);
			//printf("i,j %d ; %d \n\r", i, j);
			//_delay_ms(50);
		}
		//write_c()
	}
}

void write_arrow()
{
	printf("screen on \n\r");
	
	//write_c(0xA5);
	//_delay_ms(10);
	
	/*write_d(0b00011000);
	write_d(0b00011000);
	write_d(0b01111110);
	write_d(0b00111100);
	write_d(0b00011000);
	*/
//Arrow horizontal mode
	/*for (int i=0;i<8;i++){
	write_c(0b10110000);
	write_d(0x00000000); 
	write_c(0b10110000);
	write_d(0x00111100);
	write_c(0b10110000);
	write_d(0x00111100);
	write_c(0b10110000);
	write_d(0x00111100);
	write_c(0b10110000);
	write_d(0x11111111);
	write_c(0b10110000);
	write_d(0x01111110);
	write_c(0b10110000);
	write_d(0x00111100);
	write_c(0b10110000);
	write_d(0x00011000);
	write_c(0b10110000);
	write_d(0x00000000);
	}*/
}

void OLED_set_column(uint8_t col) //in horizontal mode
{
	if(col < 128)
	{
		write_c(0x21);
		write_c(col);
		write_c(128);
	}
}

void OLED_set_page(uint8_t page) //in horizontal mode
{
	if(page < 8)
	{
		write_c(0x22);
		write_c(page);
		write_c(7);
	}
}

void OLED_pos(uint8_t page,uint8_t col)
{
	OLED_set_page(page);
	OLED_set_column(col);
}



/*
void OLED_set_column(uint8_t column) 	//in page mode
{
    if (column < 128) {
        write_c(0x00 + (column & 0x0F));       // bitmask to set lower bits
        write_c(0x10 + ((column & 0xF0)>>4));  // bitmask to set higher bits
    }
}

void OLED_set_page(uint8_t page)		//in page mode
{
	if (page <8)
	{
		write_c(0xB0 + page);
	}
}
*/