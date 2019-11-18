#include <avr/interrupt.h>
#include "CAN_ID.h"
#include "UART.h"
//#include "accessMemory.c" //induce mistake in uart come since we added node 2
#include "usbCard.h"
#include "oled.h"
#include "MCP2515.h"
#include "SPI.h"
#include "CAN.h" 

#define RAM_SLIDER_RIGHT 0x0
#define RAM_SLIDER_LEFT  0x1
#define RAM_JOY_X 0x2
#define RAM_JOY_Y 0x3
#define EXT_RAM 0x800
#define EXT_ADC 0x1400
#define LENGTH_BUFFER_END_GAME 5

volatile uint8_t buffer_end_game[LENGTH_BUFFER_END_GAME];

// Function to manage the left slider, responsible of quitting the game
void update_left_slider()
{
	for(uint8_t i=0;i<LENGTH_BUFFER_END_GAME-1;i++)
	{
		buffer_end_game[i]=buffer_end_game[i+1];
	}
	buffer_end_game[LENGTH_BUFFER_END_GAME-1] = get_leftSlider();
	for(uint8_t i=0;i<LENGTH_BUFFER_END_GAME-1;i++)
	{
		printf("\tbuffer %dend game %d",i,buffer_end_game[i]);
		if(buffer_end_game[i]<=buffer_end_game[i+1])
		{
			return;
		}
	}
	CAN_send_quit();
}

int main(void)
{
 	uint8_t* ext_ram = (uint8_t) 0x800;
 	uint8_t* ext_adc = (uint8_t) 0x400;
 	uint8_t *ext_mem=(uint8_t) 0;

	//cli();
	DDRB = 0xFF; // all pins in the port B act as outputs
	USART_Init ( MYUBRR );
	fdevopen(USART_Transmit, USART_Receive);
	extern FILE* uart ;

	//initialisation for SRAM 
	MCUCR |= 1 << SRE; // enable external memory
	SFIOR |= 1 << XMM2; // disable flashing pins (we only use 12 pins for addressing)

	//acccess ADC

	//initialisation of buttons
	int buttonLEFT=0;
	int buttonRIGHT=0;

	//enable pins of port B (put 11 in PB1 and PB0 for the 2 buttons
	PORTB|= ~((1<<PB0)|(1<<PB1));

	//while(1) SRAM_test();

	initUsbCard();
	OLED_init();
	
	can_init(MODE_NORMAL);

	menu_init();
	
	while(1)
	{
		CAN_send_XJoystick(10); //parameter is how much we want to filter the ADC value
		printf("x_Joytick sent\t");

		update_left_slider();
		if(read_buttons()>0)
		{
			CAN_send_btns();
			printf("btns sent\t");
		}	
		CAN_send_right_slider();
		printf("right slider sent\n\r");
		printf("value sent : %d\t", get_rightSlider());
		


		//_Bool btn1 = PINB & (1 << PB0);
		//_Bool btn2 = PINB & (1 << PB1);
		/* printf("set screen to black");
		OLED_black();
		_delay_ms(1000);
		printf("set screen to white");
		OLED_white();
		_delay_ms(1000);*/
		//OLED_white();

		//write_arrow();
		//printf("Button left: %d, button right: %d \n\r", btn2, btn1);

		//_delay_ms(1000);
		//printf("sliders L/F %d , %d \n\r", ext_ram[RAM_SLIDER_LEFT],ext_ram[RAM_SLIDER_RIGHT]);
		_delay_ms(25);
	}

	    


	//while (true)
	//{
		/*ext_mem = 0x1400;
		ext_mem[1]= 1 ;
		printf("test ADC \n\r");
		_delay_ms(2000);

		ext_mem = 0x1800;
		ext_mem[1]= 1 ;
		printf("test SRAM\n\r");
		_delay_ms(2000);

		ext_mem = 0x1000;
		ext_mem[100]= 1 ;
		printf("test OLED\n\r");
		_delay_ms(2000);*/


	//}

	/*while(1)
	{

		printJoystick();
		readSliders();
		_Bool btn1 = PINB & (1 << PB0);
		_Bool btn2 = PINB & (1 << PB1);
		printf("Button left: %d, button right: %d \n\r", btn2, btn1);

		//_delay_ms(1000);
		//printf("sliders L/F %d , %d \n\r", ext_ram[RAM_SLIDER_LEFT],ext_ram[RAM_SLIDER_RIGHT]);

	}*/


/*
	//Adressing SRAM test
	while (1) SRAM_test();


	//int a=0;
    while(1)
    {
		PORTB = 0xFF;
		_delay_ms(1000);
		PORTB = 0x00;
        //USART_Transmit(USART_Receive(stream),stream);


		//USART_Receive();
		_delay_ms(1000);
		printf("3");
        //TODO:: Please write your application code
    }

*/
    return 0;
}

