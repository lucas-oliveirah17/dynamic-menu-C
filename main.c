#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "dynamic-menu.h"
#include "colors-menu.h"

void functionTestExit(){printf("Option Exit selected.\n");}
void functionTest1(){printf("Option 1 selected.\n");}
void functionTest2(){printf("Option 2 selected.\n");}
void functionTest3(){printf("Option 3 selected.\n");}
void functionTest4(){printf("Option 4 selected.\n");}
void functionTest5(){printf("Option 5 selected.\n");}
void functionTest6(){printf("Option 6 selected.\n");}

void functionSubMenu();

int main()
{
    setlocale(LC_ALL, "");

    // Create Main for Example
    Menu mainMenu;
    ItemMenu itemMainMenu[] = {
        // label, functionAction, isSelected
        {"Option 1", functionSubMenu},
        {"Option 2", functionTest2},
        {"Option 3", functionTest3},

        {"SAIR", functionTestExit}
    };
    int numberItemsMenu = sizeof(itemMainMenu) / sizeof(itemMainMenu[0]);
    int columnsMenu = 3;
    int gapMenu = 2;

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

void functionSubMenu(){
    // Create Sub Main for Example
    Menu subMenu;
    ItemMenu itemSubMenu[] = {
        // label, functionAction, isSelected
        {"Option 1", functionTest1},
        {"Option 2", functionTest2},
        {"Option 3", functionTest3},
        {"Option 4", functionTest4},
        {"Option 5", functionTest5},
        {"Option 6", functionTest6},

        {"Voltar", functionTestExit}
    };
    int numberItemsSubMenu = sizeof(itemSubMenu) / sizeof(itemSubMenu[0]);
    int columnsSubMenu = 3;
    int gapSubMenu = 2;

    subMenu = create_menu(
        "TESTE | SUB MENU DINAMICO!",
        itemSubMenu,
        numberItemsSubMenu,
        columnsSubMenu,
        gapSubMenu
    );

    run_menu(&subMenu);
}
