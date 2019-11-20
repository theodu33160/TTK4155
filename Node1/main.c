#include <avr/interrupt.h>
#include "UART.h"
//#include "accessMemory.c" //induce mistake in uart come since we added node 2
#include "usbCard.h"
#include "oled.h"
#include "menu.h"
#include "MCP2515.h"
#include "SPI.h"
#include "CAN.h" 
#include "CAN_ID.h"

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
    //At this point, we have slide along the left slider
    //if we arive at this point, we have to send a CAN message to stop the game
	CAN_send_quit();
}

int main(void)
{
 	uint8_t* ext_ram = (uint8_t) 0x800;
 	uint8_t* ext_adc = (uint8_t) 0x400;
 	uint8_t *ext_mem=(uint8_t) 0;
    //enable pins of port B (put 11 in PB1 and PB0 for the 2 buttons
    PORTB|= ~((1<<PB0)|(1<<PB1));

    USART_Init ( MYUBRR );
	fdevopen(USART_Transmit, USART_Receive);
	extern FILE* uart ;

    //initialisation for accessing external adresses
	MCUCR |= 1 << SRE; // enable external memory
	SFIOR |= 1 << XMM2; // disable flashing pins (we only use 12 pins for addressing)

    //SRAM_test();

	//initialisation
	initUsbCard();
	OLED_init();
	can_init(MODE_NORMAL);
	menu_init();
	
	while(1)
	{
		CAN_send_XJoystick(10); //parameter is how much we want to filter the ADC value
		printf("x_Joytick sent\t");
        update_left_slider(); //check if we have to quit the game
        //send button to activate the solenoïd if needed. Could have been made by interrupt
		if(read_buttons()>0)
		{
			CAN_send_btns();
			printf("btns sent\t");
		}	
		CAN_send_right_slider();
		printf("right slider sent\n\r");

        _delay_ms(25); //not to overload th CAN bus
	}
    return 0;
}

