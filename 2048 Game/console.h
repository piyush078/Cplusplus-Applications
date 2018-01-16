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
 * Set the size of the Console.
 *
 * @param  int
 * @param  int
 * @return void
 */
void setConsoleSize (short width, short height) {
    HWND console = GetConsoleWindow ();
    RECT r;
    GetWindowRect (console, &r);
    MoveWindow (console, r.left, r.top, width, height, TRUE);
}
