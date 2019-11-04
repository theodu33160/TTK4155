#include "CAN_ID.h"
#include <avr/interrupt.h>
#include "UART.h"
#include "accessMemory.c"
#include "usbCard.h"
//#include "adc.h" //trying interrupts
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


int main(void)
{


 uint8_t* ext_ram = (uint8_t) 0x800;
 uint8_t* ext_adc = (uint8_t) 0x400;
 uint8_t *ext_mem=(uint8_t) 0;

	cli();
	DDRB = 0xFF; // all pins in the port B act as outputs
	USART_Init ( MYUBRR );
	fdevopen(USART_Transmit, USART_Receive);
	extern FILE* uart ;
	printf("0");
	printf("hei\n\r");

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
/*

//	initInterrupt();
//	readADC(0x4);

	  OLED_init();
  	OLED_home();
  	OLED_black();
  	OLED_home();

  	menu_displayMainPage();
	  menu_navigate();*/

    //Self test of the SPI driver




	//mcp2515_init(MODE_CONFIG);
	//mcp2515_init(MODE_NORMAL);


	
	can_init(MODE_NORMAL);

	

/*
	can_message_send(&message);
	while(!can_transmit_complete);
	//can_message msg;
	//can_data_receive(&msg); 

/*
	can_message message1;
	message1.id= 5;
	message1.length= 1;
	message1.data[0] = (uint8_t)'W';
	can_message_send(&message1);
	while(!can_transmit_complete);
	can_message msg1;
	can_data_receive(&msg1);  
*/
		
	while(1)
	{
		/*
		int8_t angleJTCK=get_angle()/2;
		can_message message;
		message.id= 5;
		message.length= 1;
		message.data[0] = angleJTCK;
		can_message_send(&message);
		while(!can_transmit_complete);
		printf("message sent: %s\t",message.data);
		printf("CANINTF register:%x\t", mcp2515_read(MCP_CANINTF)); 
		printf("EFLG register:%x\n\r", mcp2515_read(MCP_EFLG)); 
		*/
	
	//	CAN_send_joystick_angle();
		_delay_ms(1000);


		//printJoystick();
  //  _delay_ms(1000);
		//readSliders();
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

	}

	    menu_init();


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

