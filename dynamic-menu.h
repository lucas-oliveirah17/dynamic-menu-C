#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>

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

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_BOLD          "\x1b[1m"

int showMenu();
void clearScreen();
void enableColorMod();

void functionTestExit();
void functionTest1();
void functionTest2();
void functionTest3();
void functionTest4();


