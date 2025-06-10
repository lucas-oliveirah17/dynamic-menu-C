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
    enableColorMod();
    ItemMenu mainMenu[] = {
        {"Option 1", functionTest1, true},
        {"Option 2", functionTest2, false},
        {"Option 3", functionTest3, false},
        {"Option 4", functionTest4, false},
        {"Option 5", functionTest1, false},
        {"Option 6", functionTest2, false},
        // label, functionAction, isSelected

        {"SAIR", functionTestExit, false}
    };
    int numberItemsMenu = sizeof(mainMenu) / sizeof(mainMenu[0]);

    int rowColumns = (numberItemsMenu / COLUMNS_MENU);
    if(numberItemsMenu % COLUMNS_MENU) rowColumns++;

    do{
        clearScreen();

        // HEADER MENU
        printf(ANSI_BOLD ANSI_COLOR_YELLOW
               "\n######################"
               "\nTESTE | MENU DINAMICO!"
               "\n######################\n"
               ANSI_COLOR_RESET);

        // OPTION MENU
        for(int i = 0; i < rowColumns; i++){
            printf("  ");
            for(int j = 0; j < COLUMNS_MENU; j++){
                int index = i * COLUMNS_MENU +j;
                if(index < numberItemsMenu){
                    if(mainMenu[index].isSelected)printf(ANSI_COLOR_BLUE);
                    else printf(ANSI_COLOR_GREEN);

                    printf("%-15s", mainMenu[index].label);

                    printf(ANSI_COLOR_RESET);
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

void enableColorMod(){
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if(hOut == INVALID_HANDLE_VALUE){
            fprintf(stderr, "ERRO: Nao foi possivel obter o handle do console.\n");
            return;
        }

        DWORD dwMode = 0;
        if(!GetConsoleMode(hOut, &dwMode)){
            fprintf(stderr, "ERRO: Nao foi possivel obter o modo do console.\n");
            return;
        }

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if(!SetConsoleMode(hOut, dwMode)){
            fprintf(stderr, "ERRO: Nao foi possivel ativar o modo de terminal virtual.\n");
            return;
        }
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
