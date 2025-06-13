#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dynamic-menu.h"
#include "colors-menu.h"

void clear_screen();
void enable_color_mode();
int get_column_width(ItemMenu *menu, int numberItemsMenu, int padding);
int read_key();

struct ItemMenu{
    const char* label;
    void (*functionAction)(void);
};

int showMenu(){
    ItemMenu mainMenu[] = {
        // label, functionAction, isSelected
        {"Option 1", functionTest1},
        {"Option 2", functionTest2},
        {"Option 3", functionTest3},
        {"Option 4", functionTest4},
        {"Option 5", functionTest1},
        {"Option 6", functionTest2},

        {"SAIR", functionTestExit}
    };

    int input = 0;
    int columnsMenu = 3;
    int selectedIndex = 0;
    const char* title = "\nTESTE | MENU DINAMICO!";
    int gap = 2;
    int numberItemsMenu = sizeof(mainMenu) / sizeof(mainMenu[0]);
    int columnWidth = get_column_width(mainMenu, numberItemsMenu, gap);
    bool isCommand = false;

    enable_color_mode();

    int rowsMenu = (numberItemsMenu / columnsMenu);
    if(numberItemsMenu % columnsMenu) rowsMenu++;

    do{
        clear_screen();

        // HEADER MENU
        printf(HEADER_COLOR
               "######################"
               "%s"
               "\n######################\n"
               COLOR_RESET, title);

        // OPTION MENU
        for(int i = 0; i < rowsMenu; i++){
            printf("%*s", gap, "");
            for(int j = 0; j < columnsMenu; j++){
                int index = i * columnsMenu +j;
                if(index < numberItemsMenu){
                    if(index == selectedIndex)printf(SELECTED_COLOR);
                    else printf(MENU_COLOR);

                    printf("%-*s", columnWidth, mainMenu[index].label);

                    printf(COLOR_RESET);
                }
            }
            printf("\n");
        }

        do{
            input = read_key();
            if(input){
                isCommand = true;

                switch(input){
                    case KEY_UP:
                        if(selectedIndex - columnsMenu >= 0){
                            selectedIndex -= columnsMenu;
                        }

                        else{
                            int currentColumn = selectedIndex % columnsMenu;
                            for(int i = numberItemsMenu - 1; i >= 0; i--){
                                if(i % columnsMenu == currentColumn){
                                    selectedIndex = i;
                                    break;
                                }
                            }
                        }

                        break;

                    case KEY_DOWN:

                        if(selectedIndex + columnsMenu < numberItemsMenu){
                            selectedIndex += columnsMenu;
                        }

                        else{
                            int currentColumn = selectedIndex % columnsMenu;
                            for(int i = 0; i < numberItemsMenu; i++){
                                if(i % columnsMenu == currentColumn){
                                    selectedIndex = i;
                                    break;
                                }
                            }
                        }

                        break;

                    case KEY_LEFT:
                        if(!selectedIndex){
                            selectedIndex = numberItemsMenu - 1;
                        }

                        else selectedIndex -= 1;
                        break;

                    case KEY_RIGHT:
                        if(selectedIndex == (numberItemsMenu - 1)){
                            selectedIndex = 0;
                        }
                        else selectedIndex += 1;
                        break;

                    case KEY_ENTER:
                        mainMenu[selectedIndex].functionAction();
                        system("PAUSE");
                        break;

                }
            }
        }while(!isCommand);
        isCommand = false;
    }while(1);
}

void clear_screen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif // _WIN32
}

void enable_color_mode(){
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

int get_column_width(ItemMenu *menu, int numberItemsMenu, int padding){
    int maxLabelLength = 0;
    for(int i = 0; i < numberItemsMenu; i++){
        int currentLength = strlen(menu[i].label);
        if(currentLength > maxLabelLength) maxLabelLength = currentLength;
    }

    return maxLabelLength + padding;
}

int read_key(){
    #ifdef _WIN32
        int input = _getch();

        if(input == 224) input = _getch();

        switch(input){
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
            case KEY_ENTER:
                return input;

            default:
                return INVALID_KEY;
        }

    #else
        struct termios oldt, newt;
        int input;

        // Save current terminal config
        tcgetattr(STDIN_FILENO, &oldt);

        // Copy and modify to non-canonical mode (direct reading)
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        input = getchar();
        if(input == 27){
            if(getchar() == 91) input = getchar();
        }

        switch(input){
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
            case KEY_ENTER:
                break;

            default:
                input = INVALID_KEY;
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return input;
    #endif // _WIN32
}
