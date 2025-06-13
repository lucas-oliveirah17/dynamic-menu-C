#ifndef DYNAMIC_MENU_H
#define DYNAMIC_MENU_H

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>

    #define KEY_UP 72
    #define KEY_DOWN 80
    #define KEY_LEFT 75
    #define KEY_RIGHT 77
    #define KEY_ENTER 13

#else
    #include <termios.h>
    #include <unistd.h>

    #define KEY_UP 'A'
    #define KEY_DOWN 'B'
    #define KEY_LEFT 'C'
    #define KEY_RIGHT 'D'
    #define KEY_ENTER 10

#endif // _WIN32

#define INVALID_KEY 0
#define MENU_CONTINUE 0
#define MENU_EXIT 1

typedef struct ItemMenu{
    const char* label;
    int (*functionAction)(void);
} ItemMenu;

typedef struct Menu{
    const char* title;
    ItemMenu* item;
    int columns;
    int gap;

    int selectedIndex;
    int numberItems;
    int rows;
    int columnWidth;
} Menu;

Menu create_menu(const char* title, ItemMenu* item, int numberItems, int columns, int gap);
void run_menu(Menu *menu);

#endif // DYNAMIC_MENU_H_INCLUDED
