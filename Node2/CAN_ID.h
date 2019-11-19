#ifndef CAN_ID_H
#define CAN_ID_H
// In this file we are defining the different ID for every information that might be sent via CAN from NODE1 to NODE2
#define ID_QUIT 10
#define ID_BTNS 100 // We can store 8 buttons in 1 byte. Use BTN_RIGHT, BTN_LEFT or BTN_JOYSTICK to choose the value you want.
#define ID_LEFT_SLIDER 101
#define ID_RIGHT_SLIDER 102
#define ID_JOYSTICK_X 103
#define ID_JOYSTICK_Y 104
#define ID_JOYSTICK_MAGNITUDE 105
#define ID_JOYSTICK_ANGLE 106

#define BTN_RIGHT 0
#define BTN_LEFT 1
#define BTN_JOYSTICK 2

#define UINT8   0
#define INT8    1

#endif
