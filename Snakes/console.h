#include <windows.h>

/**
 * Set the cursor to a specific position.
 *
 * @param  int
 * @param  int
 * @return void
 */
void setCursor (short x, short y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), pos);
}

/**
 * Clear the console window.
 *
 * @param void
 * @return void
 */
void clearConsole () {
    system ("cls");
}
