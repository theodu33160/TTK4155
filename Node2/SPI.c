#include "SPI.h"

void SPI_Init()
{//The AVR is the master controlling the CAN controller
    SPI_MasterInit();
}

void SPI_MasterInit(void)
{//init the microcontroler as a SPI master
    // Set MOSI, SCK and CS as output ; MISO as input
    DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK)|(1<<CAN_CS);
    DDR_SPI &= ~(1<<DD_MISO);
    // Enable SPI, Master, set clock rate fck/16
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    PORTB |= (1<<CAN_CS); //select to discuss with the CAN controller
}

void SPI_write(char cData)
{//write to the CAN controler. Can be datas or commands
    // Start transmission by putting the data in the SPI register
    SPDR = cData;

    // Wait for transmission complete
	while(!(SPSR & (1<<SPIF)))
	{
        _delay_us(100); //should not be useful, but does not work otherwise
	}
}

void SPI_SlaveInit(void)
{//init the microcontroler as a SPI slave
    // Set MISO output, all others input
    DDR_SPI = (1<<DD_MISO);

    //Enable SPI
    SPCR = (1<<SPE);
}

char SPI_read(void)
{
    SPDR = 0xFF; //starting communication with the slave
    //Wait for reception complete
    while(!(SPSR & (1<<SPIF)));

    // Return data register
    return SPDR;
}
