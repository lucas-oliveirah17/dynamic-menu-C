#include <stdio.h>
#include <stdlib.h>
#include "dynamic-menu.h"
#include "colors-menu.h"

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

int main()
{
    showMenu();
    return 0;
}
