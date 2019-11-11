// Confguration of the PWM
#include "motor.h"


void motor_init()
{
   
    //Choosing of the Waveform Generation mode
    TCCR1A |= (1<<WGM11);
    TCCR1A &= ~(1<<WGM10);
    TCCR1B |= (1<<WGM12)|(1<<WGM13);

    //Choosing Prescaler to 8
    TCCR1B &= ~(1<<CS12);
    TCCR1B |= (1<<CS11);
    TCCR1B &= ~(1<<CS10);


    DDRB |= (1<<PB7); //using pin 13 as output

    //Compare output mode non-inverting
    TCCR1A |= (1<<COM1A1);
    TCCR1A &= ~(1<<COM1A0);

   // OCR1AH = 0x00;
    //OCR1AL = 0xff;
    

    //Configuring TOP value to 255 = 1 byte. It is the same lengh of sensor data.
    ICR1H = 0x00;
    ICR1L = 0x80;
    printf("MOTOR INIT DONE\n\r");


}

void set_speed(uint8_t duty) // does speed and direction
{
    if(duty>118 && duty < 138)
    {
        OCR1CL = 0; //&0x00FF;
        PINH |= 1<<PH1 //set the pin DIR to 1
    }
    else
    {
        OCR1CL = abs(duty-128);
        PINH &= ~(1<<PH1) //set the pin DIR to 0
    }
}