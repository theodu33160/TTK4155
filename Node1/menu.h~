#ifndef MENU_H
#define MENU_H

#include "oled.h"
#include "usbCard.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

#define NB_LINES_MENU 5
#define NB_CHARACTERS 5


uint8_t checkJoystick();

//---------function management menu
void menu_init();
void menu_main();
void menu_displayMainPage();
uint8_t menu_navigate(uint8_t firstLine, uint8_t nb_subMenu);
uint8_t setSettings();
void start_game();
void showLeaderBoard();
void menu_quit();
void chooseCharacter();
void showCharChoice();





#endif
