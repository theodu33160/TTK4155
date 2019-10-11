#ifndef MENU_H
#define MENU_H

#include "oled.h"
#include "usbCard.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

#define NB_LINES_MENU 4


uint8_t checkJoystick();

//---------function management menu
voidmenu_displayMainPage();
void menu_navigate();
void setSettings();
void start_game();
void showLeaderBoard();
void menu_quit();





#endif
