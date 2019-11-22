#include "menu.h"

//-------default settings :
volatile uint8_t difficulty = 1;
char* characters[NB_CHARACTERS] = {"Mario","Peach","Luigy","inaki","claire"};

//initialisation of the menu - printing slowly Welcome to Ping Pong and below touch joysick 
void menu_init()
{
    OLED_black();
    OLED_pos(0,3*8);
    OLED_printf_slow("Welcome",50);
    OLED_pos(1,7*8);
    OLED_printf_slow("To",500);
    OLED_pos(3,20);
    OLED_printf_slow("PING - PONG",200);
    OLED_pos(7,0);
    _delay_ms(1500);
    OLED_printf("Touch Joystick");
    while(checkJoystick()==NEUTRAL)
    {
        _delay_ms(10);
    }
    while(!checkJoystick()==NEUTRAL)
    {
        _delay_ms(10);
    }
    menu_main();
}

//function that enables to choose an item in the menu : settings / choose character / start game / leader board / quit
void menu_main()
{
    menu_displayMainPage();
    uint8_t menuChoice = menu_navigate(2,NB_LINES_MENU);
    switch (menuChoice)
    {
        case 0:
            setSettings();
            break;
        case 1:
            chooseCharacter();
            break;
        case 2:
            start_game();
            break;
        case 3:
            showLeaderBoard();
            break;
        case 4:
            menu_quit();
            break;

        default:
            break;
    }

}

//function that diplay the main menu of the game 
void menu_displayMainPage()
{
    OLED_black();
    OLED_pos(0,0);
    OLED_printf(" PING-PONG Menu ");
    OLED_pos(2,0);
    OLED_printf("1 Settings"); //Settings
    OLED_pos(3,0);
    OLED_printf("2 Choose character"); //Choose character
    OLED_pos(4,0);
    OLED_printf("3 Play"); //Play
    OLED_pos(5,0);
    OLED_printf("4 Leader Board"); //Leader Board
    OLED_pos(6,0);
    OLED_printf("5 Quit"); //Quit
    OLED_pos(2,0); //retour à la première ligne du menu
    write_char_inv('1');
}

//function that enable to navigate in the menu
uint8_t menu_navigate(uint8_t firstLine, uint8_t nb_subMenu)
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
                    menu_pos++;
                    if(menu_pos ==nb_subMenu) menu_pos = 0;
                    OLED_pos(menu_pos + firstLine,0);
                    write_char_inv(menu_pos + 49);
                    actionAllowed=false;
                    break;
                case UP:
                    OLED_pos(menu_pos + firstLine,0);
                    write_char(menu_pos+49);
                    if (menu_pos == 0) menu_pos = nb_subMenu-1;
                    else menu_pos--;
                    OLED_pos(menu_pos + firstLine,0);
                    write_char_inv(menu_pos + 49);
                    actionAllowed=false;
                    break;
                case LEFT:
                    actionAllowed=false;
                    menu_main();
                    break;
                case RIGHT:
                case PUSH:
                    actionAllowed=false;
                    return menu_pos;
                    break;

                default:
                  //  printf("unknown case in the navigation in the menu");
                    break;
            }
        }
    }
}


// function that returns the direction of the joystick (NEUTRAL / LEFT / RIGHT / UP / DOWN)
uint8_t checkJoystick()
{
    if (!read_button(BTN_JOYSTICK)) return PUSH;
    else return get_direction();
}

//function that 'open' a setting page to pick the difficulty of the game
uint8_t setSettings()
{
    OLED_black();
    OLED_pos(0,0);
    OLED_printf("Setting page");
    OLED_pos(2,0);
    OLED_printf("difficulty ? ");
    //chosing the difficulty with the joystick
    _Bool joystick_pressed =false;
    while(1)
    {
        OLED_pos(2,13*8);
        write_char(difficulty+48);
        switch(checkJoystick())
        {
            case PUSH:
            case LEFT:
                menu_main();
                return difficulty;
            break;
            case DOWN:
		if(!joystick_pressed)
		{
		    if (difficulty>1) difficulty--;
		    joystick_pressed = true;
		}
                break;
            case UP:
		if(!joystick_pressed)
		{
                    if (difficulty<9) difficulty++;
		    joystick_pressed = true;
		}
                break;
            default:
		joystick_pressed = false;
                break;
        }
    }

}

//function that 'open' a page to pick a character
void chooseCharacter()
{
    showCharChoice();
    while(checkJoystick()!=NEUTRAL) {_delay_ms(10);}
    uint8_t charChoice = menu_navigate(3,NB_CHARACTERS);
    OLED_black();
    OLED_pos(1,1);
    OLED_printf("Good choice:");
    OLED_pos(2,0);
    OLED_printf("You have chosen");
    OLED_pos(4,0);
    OLED_printf(characters[charChoice]);
    _delay_ms(3000);//can be change to the press of a random button
    menu_main();
}

//function that 'open' a page to start playing ping pong
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
}

//function that enables to show the leader board
void showLeaderBoard()
{
    OLED_black();
    OLED_pos(0,0);
    OLED_printf("Leader Board");
    OLED_pos(2,0);
    OLED_printf("1 AZERTY <3");
    OLED_pos(3,0);
    OLED_printf("2 Stud. assist.");
    while(checkJoystick()!=LEFT)
    {
        _delay_ms(10);
    }
    main_menu();
}

//function that turns off the screen
void menu_quit()
{
    OLED_black();
    while(1);
}


//function to choose the character
void showCharChoice()
{
    OLED_black();
    OLED_pos(0,0);
    OLED_printf("Choose character");
    OLED_pos(1,0);
    //OLED_printf("Go right for ?"); //the question mark is because there is not enough room to write more : missing one char.

    for(uint8_t i = 0;i<NB_CHARACTERS;i++)
    {
        OLED_pos(3+i,0);
        write_char(i+49);
        write_char(' ');
        OLED_printf(characters[i]);
    }
}
