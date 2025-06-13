#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "dynamic-menu.h"
#include "colors-menu.h"

// Function for tests
int functionTestExit(){return MENU_EXIT;}
int functionTest1(){printf("Option 1 selected.\n"); system("PAUSE"); return 0;}
int functionTest2(){printf("Option 2 selected.\n"); system("PAUSE"); return 0;}
int functionTest3(){printf("Option 3 selected.\n"); system("PAUSE"); return 0;}
int functionTest4(){printf("Option 4 selected.\n"); system("PAUSE"); return 0;}
int functionTest5(){printf("Option 5 selected.\n"); system("PAUSE"); return 0;}
int functionTest6(){printf("Option 6 selected.\n"); system("PAUSE"); return 0;}

int call_SubMenu();

int main()
{
    setlocale(LC_ALL, "");

    // Create Main for Example
    Menu mainMenu;
    ItemMenu itemMainMenu[] = {
        // label, functionAction
        {"SUBMENU", call_SubMenu},
        {"Option 1", functionTest1},
        {"Option 2", functionTest2},

        {"SAIR", functionTestExit}
    };
    int numberItemsMenu = sizeof(itemMainMenu) / sizeof(itemMainMenu[0]);
    int columnsMenu = 2;
    int gapMenu = 4;

    mainMenu = create_menu(
        "TESTE | MENU DINAMICO!",
        itemMainMenu,
        numberItemsMenu,
        columnsMenu,
        gapMenu
    );

    run_menu(&mainMenu);
    return 0;
}

int call_SubMenu(){
    // Create Sub Main for Example
    Menu menu;
    ItemMenu itemMenu[] = {
        // label, functionAction, isSelected
        {"Option 1", functionTest1},
        {"Option 2", functionTest2},
        {"Option 3", functionTest3},
        {"Option 4", functionTest4},
        {"Option 5", functionTest5},
        {"Option 6", functionTest6},

        {"VOLTAR", functionTestExit}
    };
    int numberItemsMenu = sizeof(itemMenu) / sizeof(itemMenu[0]);
    int columnsMenu = 3;
    int gapMenu = 4;

    menu = create_menu(
        "TESTE | SUB MENU DINAMICO!",
        itemMenu,
        numberItemsMenu,
        columnsMenu,
        gapMenu
    );

    run_menu(&menu);
    return 0;
}
