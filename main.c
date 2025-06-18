#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "dynamic-menu.h"
#include "colors-menu.h"

// Function for tests
int functionTestExit(){return MENU_FLOW_EXIT;}
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
    MenuOpStatus status;

    // Create Main for Example
    Menu mainMenu;
    ItemMenu itemMainMenu[] = {
        // label, functionAction, argument
        {.label = "SUBMENU", .action = call_SubMenu},
        {.label = "Option 1", .action = functionTest1},
        {.label = "Option 2", .action = functionTest2},

        {"SAIR", functionTestExit}
    };
    int columnsMenu = 2;
    int gapMenu = 3;

    mainMenu = CREATE_MENU(
        "TESTE | MENU DINAMICO!",
        itemMainMenu,
        columnsMenu,
        gapMenu
    );

    status = disable_item(&mainMenu, "Option 2");
    if(status == MENU_OP_ITEM_NOT_FOUND){
        printf("\nERROR: Label not found!\n");
        return MENU_OP_ITEM_NOT_FOUND;
    }

    run_menu(&mainMenu);
    return 0;
}

int call_SubMenu(){
    // Create Sub Main for Example
    Menu menu;
    ItemMenu itemMenu[] = {
        {.label = "Option 1", .action = functionTest1},
        {.label = "Option 2", .action = functionTest2},
        {.label = "Option 3", .action = functionTest3},
        {.label = "Option 4", .action = functionTest4},
        {.label = "Option 5", .action = functionTest5},
        {.label = "Option 6", .action = functionTest6},

        {"VOLTAR", functionTestExit}
    };

    int columnsMenu = 2;
    int gapMenu = 3;

    menu = CREATE_MENU(
        "TESTE | SUB MENU DINAMICO!",
        itemMenu,
        columnsMenu,
        gapMenu
    );

    run_menu(&menu);
    return 0;
}
