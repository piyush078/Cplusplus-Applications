#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "console.h"
#include "config.h"
#include "display.h"
using namespace std;

/**
 * Prototypes of the functions declared.
 */
bool welcomeScreen (void);

/**
 * Show welcome screen.
 *
 * @param  void
 * @return boolean
 */
bool welcomeScreen () {
    char ch;
    printBoundaries ({ _LEFT_LIMIT, _TOP_LIMIT }, { _RIGHT_LIMIT, _BOTTOM_LIMIT });
    consoleLog ("SNAKES GAME", _LEFT_LIMIT, _RIGHT_LIMIT, (_TOP_LIMIT + _BOTTOM_LIMIT) / 2);
    consoleLog ("Press 'P' to play and 'Q' to quit", _LEFT_LIMIT, _RIGHT_LIMIT, _BOTTOM_LIMIT + 2);
    do {
        ch = getch ();
    } while (ch != 'q' && ch != 'Q' && ch != 'p' && ch != 'P' && ch != 27 && ch != 13);
    
    /* If the user wants to play */
    return (ch == 'p' || ch == 'P' || ch == 13);
}

/**
 * Main function.
 *
 * @param  void
 * @return int
 */
int main () {
    srand (time (NULL));
    if (welcomeScreen ()) {
        clearConsole ();
    }
    return 0;
}
