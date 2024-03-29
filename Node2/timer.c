// Confguration of the PWM
#include "timer.h"

//initialisation of PWM
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


    DDRB |= (1<<PB5); //OC1A as output

    //Compare output mode non-inverting
    TCCR1A |= (1<<COM1A1);
    TCCR1A &= ~(1<<COM1A0);

    

    //Configuring TOP value to have a Period of 0.02 s 
    ICR1H = 0x9C;
    ICR1L = 0x40;
    printf("PWM INIT DONE\r\n");


}

//set the pwm according to the duty
void set_PWM(uint8_t duty)
{
    if (duty < 70) duty = 70;
    if (duty > 200) duty = 200;
    uint16_t ocr = duty*20;
    OCR1AH = (ocr&0xFF00)>>8;
    OCR1AL = ocr&0x00FF;

}

//function that send the command to move to the servo according to the joystick position
void set_servo(int xJoystick)
{
    uint8_t res = (uint8_t) ((xJoystick-30)*13/20+70);
    set_PWM(res); //with xJoystick from 30 to 228
}
