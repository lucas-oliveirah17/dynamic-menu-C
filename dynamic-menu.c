#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dynamic-menu.h"

#define COLUMNS_MENU 2

typedef struct{
    const char* label;
    void (*functionAction)(void);
    bool isSelected;
}ItemMenu;

int showMenu(){
    ItemMenu mainMenu[] = {
        {"Option 1", functionTest1, true},
        {"Option 2", functionTest2, false},
        {"Option 3", functionTest3, false},
        {"Option 4", functionTest4, false},
        {"SAIR", functionTestExit, false}
    };
    int numberItemsMenu = sizeof(mainMenu) / sizeof(mainMenu[0]);

    int rowColumns = (numberItemsMenu / COLUMNS_MENU);
    if(numberItemsMenu % COLUMNS_MENU) rowColumns++;

    do{
        clearScreen();
        printf("\n######################");
        printf("\nTESTE | MENU DINAMICO!");
        printf("\n######################\n");

        for(int i = 0; i < rowColumns; i++){
            printf("  ");
            for(int j = 0; j < COLUMNS_MENU; j++){
                int index = i * COLUMNS_MENU +j;
                if(index < numberItemsMenu){
                    printf("%s\t", mainMenu[index].label);
                }
            }
            printf("\n");
        }
        system("PAUSE");
    }while(1);
}

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif // _WIN32
}

void functionTestExit(){
    printf("Option Exit selected.\n");
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
