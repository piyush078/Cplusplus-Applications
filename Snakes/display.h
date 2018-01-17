#include <windows.h>
#define COORD std::pair<short,short>

/**
 * Print a string on the console.
 *
 * @param  string|char
 * @param  int, int
 * @param  boolean
 * @return void
 */
void consoleLog (std::string message, short x1, short x2, short y) {
    setCursor ((x1 + x2 - message.length ()) / 2, y);
    std::cout << message;
}

void consoleLog (char ch, short x, short y) {
    setCursor (x, y);
    std::cout << ch;
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
        consoleLog ('+', x, topLeft.second);
        consoleLog ('+', x, bottomRight.second);
    }
    
    /* Draw vertical boundaries */
    for (short y=topLeft.second; y<=bottomRight.second; ++y) {
        consoleLog ('+', topLeft.first, y);
        consoleLog ('+', bottomRight.first, y);
    }
}
