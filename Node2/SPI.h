#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
//#include <avr/common.h>
#include <stdio.h>


#define DDR_SPI DDRB
#define DD_MISO PB3
#define DD_MOSI PB2
#define CAN_CS PB7
#define DD_SCK PB1
void SPI_MasterInit(void);

void SPI_write(char cData);

void SPI_SlaveInit(void);

char SPI_read(void);

void SPI_Init();



#endif