// Confguration of the PWM
#include "timer.h"
#include <avr/interrupt.h>

void PWM_init()
{
   
    //Choosing of the Waveform Generation mode
    TCCR1A |= (1<<WGM11);
    TCCR1A &= ~(1<<WGM10);
    TCCR1B |= (1<<WGM12)|(1<<WGM13);

    //Choosing Prescaler to 8
    TCCR1B &= ~(1<<CS12);
    TCCR1B |= (1<<CS11);
    TCCR1B &= ~(1<<CS10);


    DDRB |= (1<<PB5); //OC1A

    //Compare output mode non-inverting
    TCCR1A |= (1<<COM1A1);
    TCCR1A &= ~(1<<COM1A0);

   // OCR1AH = 0x00;
    //OCR1AL = 0xff;
    

    //Configuring TOP value to have a Period of 0.02 s 
    ICR1H = 0x9C;
    ICR1L = 0x40;
    printf("INIT DONE");


}

void set_PWM(uint8_t duty)
{
    if ((duty >= 70)&&(duty <= 200))
    {
        uint16_t ocr = duty*20;
        OCR1AH = (ocr&0xFF00)>>8;
        OCR1AL = ocr&0x00FF;
        //OCR1AH = 0x00;
        //OCR1AL = 0xff;
        printf("\n\rOCR1AH: %d\n\r",OCR1AH);
        printf("OCR1AL:  %d\n\r",OCR1AL);
        printf("duty OK \n\r");
    }
}

void set_servo(int8_t xJoystick)
{
    set_PWM(uint8_t 130/200*(xJoystick+100)+70); //with xJoystick from -100 to +100
}

void normal_mode()
{

} 

void IC_measure()
{

}
