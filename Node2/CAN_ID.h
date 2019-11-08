#ifndef CAN_ID_H
#define CAN_ID_H


#define ID_BTNS 100 //we can store 8 buttons in 1 byte. Use BTN_RIGHT, BTN_LEFT or BTN_JOYSTICK to choose the value you want.
#define ID_LEFT_SLIDER 101
#define ID_RIGHT_SLIDER 102
#define ID_JOYSTICK_X 103
#define ID_JOYSTICK_Y 104
#define ID_JOYSTICK_MAGNITUDE 105
#define ID_JOYSTICK_ANGLE 106

/*
#define ID_USB_CARD     100
#define LENGTH_USB_CARD 7
*/
#define UINT8   0
#define INT8    1

//enum Usb_card_type {ID_BTNS = UINT8, ID_LEFT_SLIDER = UINT8, ID_RIGHT_SLIDER = UINT8, ID_JOYSTICK_X = INT8, ID_JOYSTICK_Y = INT8, ID_JOYSTICK_MAGNITUDE = UINT8, ID_JOYSTICK_ANGLE = INT8};
//enum USB_list_name = {"BTN_right","BTN_left","BTN_joystick","left_slider","right_slider","joystick_X","joystick_Y","joystick_magnitude","joystick_angle"};
//enum USB_list_name {ID_BTNS="BTN",ID_LEFT_SLIDER="left_slider",ID_RIGHT_SLIDER="right_slider",ID_JOYSTICK_X="joystick_X",ID_JOYSTICK_Y="joystick_Y",ID_JOYSTICK_MAGNITUDE="joystick_magnitude",ID_JOYSTICK_ANGLE="joystick_angle"};
#endif