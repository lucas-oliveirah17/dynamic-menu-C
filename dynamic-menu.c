#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dynamic-menu.h"

typedef struct{
    const char* label;
    void (*functionAction)(void);
    bool isSelected;
}ItemMenu;

int showMenu(){
    ItemMenu mainMenu[] = {
        {"Option 1", functionTest1, false},
        {"Option 2", functionTest2, false}
    };
    int numberItemsMenu = sizeof(mainMenu) / sizeof(mainMenu[0]);
}

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif // _WIN32
}


void functionTest1(){
    printf("Option 1 selected.\n");
}

void functionTest2(){
    printf("Option 2 selected.\n");
}

void functionTest3(){
    printf("Option 3 selected.\n");
}
void functionTest4(){
    printf("Option 4 selected.\n");
}
