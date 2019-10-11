#include "menu.h"

//-------default settings :
uint8_t difficulty = 1;
char* characters[NB_CHARACTERS] = {"Mario","Peach","Luigy","Browser"};

void menu_init()
{
    OLED_black();
    OLED_pos(0,3);
    OLED_printf_slow("Welcome",50);
    OLED_pos(1,7);
    OLED_printf("To");
    OLED_pos(0,2);
    OLED_printf_slow("PING - PONG",200);
    OLED_pos(0,5);
    _delay_ms(500);
    OLED_printf("Touch Joystick");
    while(checkJoystick()==NEUTRAL)
    {
        _delay_ms(10);
    }
    menu_main();
}


void menu_main()
{
    menu_displayMainPage();
    uint8_t menuChoice = menu_navigate(2);
    switch (menuChoice)
    {
        case 0:
            setSettings();
            //Should we return to the main menu ?
            break;
        case 1:
            chooseCharacter();
            //Should we return to the main menu ?
            break;
        case 2:
            start_game();
            //Should we return to the main menu ?
            break;
        case 3:
            showLeaderBoard();
            //Should we return to the main menu ?
            break;
        case 4:
            menu_quit();
            //Should we return to the main menu ?
            break;

        default:
            //Should we return to the main menu ?
            break;
    }

}

void menu_displayMainPage()
{
    OLED_black();
    OLED_pos(0,0);
    OLED_printf(" PING-PONG Menu ");
    OLED_pos(2,0);
    OLED_printf("1 Settings"); //Settings
    OLED_pos(3,0);
    OLED_printf("2 Play"); //Play
    OLED_pos(4,0);
    OLED_printf("3 Choose character"); //Play
    OLED_pos(5,0);
    OLED_printf("4 Leader Board"); //Leader Board
    OLED_pos(6,0);
    OLED_printf("5 Quit"); //Quit
    OLED_pos(2,0); //retour à la première ligne du menu
    write_char_inv('1');
}

uint8_t menu_navigate(uint8_t firstLine)
{
    uint8_t menu_pos = 0;
    _Bool actionAllowed = true;
    uint8_t action = NEUTRAL;

    while(1)
    {
        action = checkJoystick();
        if(action==NEUTRAL) actionAllowed = true;
        if(actionAllowed)
        {
            switch(action)
            {
                case DOWN:
                    OLED_pos(menu_pos + firstLine,0);
                    write_char(menu_pos+49);
                    if(menu_pos ==NB_LINES_MENU) menu_pos = 0;
                    else menu_pos++;
                    OLED_pos(menu_pos + firstLine,0);
                    write_char_inv(menu_pos + 49);
                    actionAllowed=false;
                    break;

                case UP:
                    OLED_pos(menu_pos + firstLine,0);
                    write_char(menu_pos+49);
                    if (menu_pos == 0) menu_pos = NB_LINES_MENU;
                    else menu_pos--;
                    OLED_pos(menu_pos + firstLine,0);
                    write_char_inv(menu_pos + 49);
                    actionAllowed=false;
                    break;

                case RIGHT:
                case PUSH:
                    return menu_pos;
                    break;

                default:
                  //  printf("unknown case in the navigation in the menu");
                    break;
            }
        }
    }
}

uint8_t checkJoystick()
{//this function should check if we use the joystick
// We should be carefull not to have a doble push if we let the joystick in one position
// or at least put a delay !
    if (!read_button(BTN_JOYSTICK)) return PUSH;
    else return get_direction();


}

uint8_t setSettings()
{
    OLED_black();
    OLED_pos(0,0);
    OLED_printf("Setting page");
    OLED_pos(2,0);
    OLED_printf("difficulty ? ");
    //add something to chose the difficulty
    while(1)
    {
        OLED_pos(2,13);
        write_char(difficulty+48);
        switch(checkJoystick())
        {
            case PUSH:
            case LEFT:
                menu_main();
                return difficulty;
            break;
            case DOWN:
                if (difficulty>1) difficulty--;
                break;
            case UP:
                if (difficulty<9) difficulty++;
                break;
            default:
                break;

        }
    }

}

void chooseCharacter()
{
    showCharChoice();
    uint8_t charChoice = menu_navigate(3);
    OLED_black();
    OLED_pos(1,1);
    OLED_printf("Good choice:");
    OLED_pos(2,0);
    OLED_printf("You have chosen");
    OLED_pos(4,0);
    OLED_printf(characters[charChoice]);
    _delay_ms(1000);//can be change to the press of a random button
    menu_main();
}

void start_game()
{
    OLED_black();
    OLED_pos(0,0);
    OLED_printf(" PING-PONG game ");
    OLED_pos(2,0);
    OLED_printf("Loading");
    OLED_pos(3,0);
    for (uint8_t i = 0;i<16;i++)
    {
        OLED_printf(".");
        _delay_ms(200);
    }
    while(1)
    {
	if(checkJoystick()==LEFT)
	{
            menu_main();
	}
    }

}

void showLeaderBoard()
{
    OLED_black();
    OLED_pos(0,0);
    OLED_printf("Leader Board");
    OLED_pos(2,0);
    OLED_printf("1 AZERTY <3");
    OLED_pos(3,0);
    OLED_printf("2 Stud. assist.");
    while(1)
    {
        if(checkJoystick()==LEFT)
        {
            menu_main();
        }
    }

}

void menu_quit()
{
    OLED_black();
    while(1);
}


void showCharChoice()
{
    OLED_black();
    OLED_pos(0,0);
    OLED_printf("Choose character");
    OLED_pos(1,0);
    OLED_printf("Go right for ?  e"); //the question mark is because there is not enough room to write more : missing one char.

    for(uint8_t i = 0;i<NB_CHARACTERS;i++)
    {
        OLED_pos(3+i,0);
        write_char(i+49);
        write_char(' ');
        OLED_printf(characters[i]);
    }
}
