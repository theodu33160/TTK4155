#ifndef CAN_ID_H
#define CAN_ID_H


#define ID_BTNS 100 //we can store 8 buttons in 1 byte. Use BTN_RIGHT, BTN_LEFT or BTN_JOYSTICK to choose the value you want.
//#define ID_BTN_LEFT 101
//#define ID_BTN_JOYSTICK 102
#define ID_LEFT_SLIDER 103
#define ID_RIGHT_SLIDER 104
#define ID_JOYSTICK_X 105
#define ID_JOYSTICK_Y 106
#define ID_JOYSTICK_MAGNITUDE 107
#define ID_JOYSTICK_ANGLE 108

/*
#define ID_USB_CARD     100
#define LENGTH_USB_CARD 7
*/
#define UINT8   0
#define INT8    1

enum Usb_card_type = {UINT8,UINT8,UINT8,INT8,INT8,UINT8,INT8};
//enum USB_list_name = {"BTN_right","BTN_left","BTN_joystick","left_slider","right_slider","joystick_X","joystick_Y","joystick_magnitude","joystick_angle"};
enum USB_list_name = {"BTN","left_slider","right_slider","joystick_X","joystick_Y","joystick_magnitude","joystick_angle"};

#endif
