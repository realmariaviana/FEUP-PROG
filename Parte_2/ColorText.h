/* PROG - MIEIC
 * JAS
 * Example of a program that prints colored characters on the console (in text mode)
 * LINUX version, using ANSI escape sequences
 */

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>

using namespace std;

//TEXT COLOR CODES
#define NO_COLOR      "\033[0m"
#define BLACK         "\033[0;30m"
#define RED           "\033[0;31m"
#define GREEN         "\033[0;32m"
#define BROWN         "\033[0;33m"
#define BLUE          "\033[0;34m"
#define MAGENTA       "\033[0;35m"
#define CYAN          "\033[0;36m"
#define LIGHTGRAY     "\033[0;37m"
#define DARKGRAY      "\033[1;30m"
#define LIGHTRED      "\033[1;31m"
#define LIGHTGREEN    "\033[1;32m"
#define YELLOW        "\033[1;33m"
#define LIGHTBLUE     "\033[1;34m"
#define LIGHTMAGENTA  "\033[1;35m"
#define LIGHTCYAN     "\033[1;36m"
#define WHITE         "\033[1;37m"

//BACKGROUND COLOR CODES
#define BLACK_B       "\033[0;40m"
#define RED_B         "\033[0;41m"
#define GREEN_B       "\033[0;42m"
#define YELLOW_B      "\033[0;43m"
#define BLUE_B        "\033[0;44m"
#define MAGENTA_B     "\033[0;45m"
#define CYAN_B        "\033[0;46m"
#define WHITE_B       "\033[1;47m"

/* Position the cursor at column 'x', line 'y'
 * The coodinates of upper left corner of the screen are (x,y)=(0,0)
 */
void gotoxy(int x, int y);

/* Clear the screen
 */
void clrscr(void);

/* Set text color
 */
void setcolor(string color);

/* Set text color & background
 */
void setcolor(string color, string background_color);
