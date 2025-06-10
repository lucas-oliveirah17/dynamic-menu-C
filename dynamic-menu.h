#ifdef _WIN32
    #include <conio.h>

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

int showMenu();
void clearScreen();

void functionTestExit();
void functionTest1();
void functionTest2();
void functionTest3();
void functionTest4();


