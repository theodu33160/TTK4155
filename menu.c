#include "menu.h"

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
    OLED_printf("3 Leader Board"); //Leader Board
    OLED_pos(5,0);
    OLED_printf("4 Quit"); //Quit
    OLED_pos(2,0); //retour à la première ligne du menu
    write_char_inv('1');
}

void menu_navigate()
{
    uint8_t menu_pos = 0;
    _Bool actionAllowed = true;

    while(1)
    {
        uint8_t action = checkJoystick();
	
        if(action==NEUTRAL) actionAllowed = true;
        if(actionAllowed && action != NEUTRAL)
        {
            switch(action)
            {
                case DOWN:
		    printf("case DOWN");
                    OLED_pos(menu_pos+2,0);
                    printf("menu_pos = %d\n\r",menu_pos );
                    write_char(menu_pos+49);
                    menu_pos = (menu_pos + 1)  % NB_LINES_MENU;
                    printf("menu_pos1 = %d\n\r",menu_pos );
                    OLED_pos(menu_pos+2,0);
                    printf("menu_pos2 = %d\n\r",menu_pos );
		    write_char_inv(menu_pos + 49);
                    actionAllowed=false;
                    break;

                case UP:
 		    OLED_pos(menu_pos+2,0);
		    printf("case UP");
		    write_char(menu_pos+49);
		    if (menu_pos == 0){
			menu_pos = 3;
		    }
		    else{
			menu_pos--;
		    }
                    
                    OLED_pos(menu_pos+2,0);
		    write_char_inv(menu_pos + 49);
                    actionAllowed=false;
                    break;
		case RIGHT:
                case PUSH:
		    printf("action : %d\n\r",action);
		    printf("case PUSH");
                    switch (menu_pos)
                    {
                        case 0:
                            setSettings();
                            //Should we return to the main menu ?
                            break;
                        case 1:
                            start_game();
                            //Should we return to the main menu ?
                            break;
                        case 2:
                            showLeaderBoard();
                            //Should we return to the main menu ?
                            break;
                        case 3:
                            menu_quit();
                            //Should we return to the main menu ?
                            break;

                        default:
                            //Should we return to the main menu ?
                            break;
                    }
                    actionAllowed=false;
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

void setSettings()
{
    OLED_black();
    OLED_pos(0,0);
    OLED_printf("Setting page");
    OLED_pos(2,0);
    OLED_printf("difficulty ? 1");
    //add something to chose the difficulty
    while(1)
    {
	if(checkJoystick()==LEFT)
	{
	    menu_displayMainPage();
	    menu_navigate();
	}
    }

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
	    menu_displayMainPage();
	    menu_navigate();
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
	    menu_displayMainPage();
	    menu_navigate();
	}
    }

}

void menu_quit()
{
    OLED_black();
    while(1);
}
