#include <windows.h>

/**
 * Print a statement on the console.
 *
 * @param  string|int
 * @param  int, int
 * @return void
 */
void printMessage (std::string message, short x, short y) {
    setCursor (x, y);
    std::cout << message;
}

void printMessage (int message, short x, short y) {
    setCursor (x, y);
    std::cout << message;
}

/**
 * Print a character continuously on the console.
 *
 * @param  char
 * @param  int, int, int
 * @return void
 */
void printCharacters (char ch, short x1, short x2, short y) {
    setCursor (x1, y);
    for (short i=x1; i<=x2; ++i) {
        std::cout << ch;
    }
}
