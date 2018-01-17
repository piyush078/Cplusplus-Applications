#include <windows.h>
#define COORD std::pair<short,short>

/**
 * Print a string on the console.
 *
 * @param  string
 * @param  int, int
 * @param  boolean
 * @return void
 */
void consoleLog (std::string message, short x1, short x2, short y, bool center = true) {
    if (center) setCursor ((x1 + x2 - message.length ()) / 2, y);
    else setCursor (x1, y);
    std::cout << message;
}

/**
 * Draw boundaries.
 *
 * @param  struct, struct
 * @return void
 */
void printBoundaries (COORD topLeft, COORD bottomRight) {
    
    /* Draw horizontal boundaries */
    for (short x=topLeft.first; x<=bottomRight.first; ++x) {
        consoleLog ("+", x, 0, topLeft.second, false);
        consoleLog ("+", x, 0, bottomRight.second, false);
    }
    
    /* Draw vertical boundaries */
    for (short y=topLeft.second; y<=bottomRight.second; ++y) {
        consoleLog ("+", topLeft.first, 0, y, false);
        consoleLog ("+", bottomRight.first, 0, y, false);
    }
}
