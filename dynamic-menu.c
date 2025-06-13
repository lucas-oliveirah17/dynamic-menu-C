#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dynamic-menu.h"
#include "colors-menu.h"

int display_menu(Menu *menu);
int read_key();
void clear_screen();
void enable_color_mode();
int get_column_width(ItemMenu *menu, int numberItemsMenu, int padding);

Menu create_menu(const char* title, ItemMenu* item, int numberItems, int columns, int gap){
    Menu menu;

    menu.title = title;
    menu.item = item;
    menu.numberItems = numberItems;
    menu.columns = columns;
    menu.gap = gap;

    menu.selectedIndex = 0;

    menu.rows = menu.numberItems / menu.columns;
    if(menu.numberItems % menu.columns) menu.rows++;

    menu.columnWidth = get_column_width(menu.item, menu.numberItems, menu.gap);

    return menu;
}


void run_menu(Menu *menu){
    int input = 0;
    bool isCommand = false;

    enable_color_mode();

    do{
        display_menu(menu);


        do{
            input = read_key();
            if(input){
                isCommand = true;

                switch(input){
                    case KEY_UP:
                        if(menu->selectedIndex - menu->columns >= 0){
                            menu->selectedIndex -= menu->columns;
                        }

                        else{
                            int currentColumn = menu->selectedIndex % menu->columns;
                            for(int i = menu->numberItems - 1; i >= 0; i--){
                                if(i % menu->columns == currentColumn){
                                    menu->selectedIndex = i;
                                    break;
                                }
                            }
                        }
                        break;

                    case KEY_DOWN:

                        if(menu->selectedIndex + menu->columns < menu->numberItems){
                            menu->selectedIndex += menu->columns;
                        }

                        else{
                            int currentColumn = menu->selectedIndex % menu->columns;
                            for(int i = 0; i < menu->numberItems; i++){
                                if(i % menu->columns == currentColumn){
                                    menu->selectedIndex = i;
                                    break;
                                }
                            }
                        }
                        break;

                    case KEY_LEFT:
                        if(menu->selectedIndex == 0){
                            menu->selectedIndex = menu->numberItems - 1;
                        }

                        else menu->selectedIndex -= 1;
                        break;

                    case KEY_RIGHT:
                        if(menu->selectedIndex == (menu->numberItems - 1)){
                            menu->selectedIndex = 0;
                        }
                        else menu->selectedIndex += 1;
                        break;

                    case KEY_ENTER:
                        menu->item[menu->selectedIndex].functionAction();
                        system("PAUSE");
                        break;

                }
            }
        }while(!isCommand);
        isCommand = false;
    }while(1);
}

int display_menu(Menu *menu){
    char *headerBorder;
    size_t lengthHeaderBorder;

    lengthHeaderBorder = strlen(menu->title);

    headerBorder = (char*) malloc(lengthHeaderBorder + 1);
    if(headerBorder == NULL){
        printf("\nError: Failed to allocate memory!\n");
        return 1;
    }

    memset(headerBorder, '#', lengthHeaderBorder);
    headerBorder[lengthHeaderBorder] = '\0';

    clear_screen();

    // HEADER MENU
    printf(HEADER_COLOR
           "\n%s"
           "\n%s"
           "\n%s\n"
           COLOR_RESET,
           headerBorder, menu->title, headerBorder);

    // OPTION MENU
    for(int i = 0; i < menu->rows; i++){
        printf("%-*s", menu->gap, "");
        for(int j = 0; j < menu->columns; j++){
            int index = i * menu->columns +j;
            if(index < menu->numberItems){
                if(index == menu->selectedIndex)printf(SELECTED_COLOR);
                else printf(MENU_COLOR);

                printf("%-*s", menu->columnWidth, menu->item[index].label);

                printf(COLOR_RESET);
            }
        }
        printf("\n");
    }

    free(headerBorder);
    return 0;
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
