#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include "class.h"
#include "console.h"
#include "display.h"

#define BOXES vector<vector<Box>>
#define DIFFERENCE_X 8  /* Grid boxes padding x-axis */
#define DIFFERENCE_Y 4  /* Grid boxes padding y-axis */
#define INIT_X 6  /* Center position of top left box x-coordinate */
#define INIT_Y 6  /* Center position of top left box y-coordinate */

#define NUMBER_OF_BOXES 4  /* Number of boxes in a row */
enum Key { UP, RIGHT, DOWN, LEFT };  /* Codes of the keys pressed */
using namespace std;

/**
 * Get the max limit of x and y coordinates
 *
 * @param  int
 * @return pair
 */
COOR getMaxCoor (short skip = 0) {
    return {
        INIT_Y + skip + DIFFERENCE_Y * NUMBER_OF_BOXES,
        INIT_X + skip + DIFFERENCE_X * NUMBER_OF_BOXES
    };
}

/**
 * Set up the initial screen.
 *
 * @param  void
 * @return void
 */
void initializeScreen () {
    setConsoleSize (600, 600);
    printCharacters ('=', 0, getMaxCoor ().second, 0);
    printCharacters ('=', 0, getMaxCoor ().second, 2);
    printMessage ("2048 Game", 2, 1);
    
    short x1 = INIT_X - DIFFERENCE_X / 2, y,
          x2 = getMaxCoor ().second - DIFFERENCE_X / 2,
          y1 = INIT_Y - DIFFERENCE_Y / 2,
          y2 = getMaxCoor ().first - DIFFERENCE_Y / 2;
    
    for (short x=x1; x<=x2; x+=DIFFERENCE_X) {
        for (short y=y1; y<=y2; ++y) {
            printCharacters ('|', x, x, y);
        }
    }
    for (short i=0; i<=NUMBER_OF_BOXES; ++i) {
        y = y1 + i * DIFFERENCE_Y;
        printCharacters ('=', x1, x2, y);
    }
    printMessage ("Press 'P' to play.", 2, y2+2);
}

/**
 * Assign the console positions to the boxes.
 *
 * @param  array
 * @return void
 */
void assignCoordinates (BOXES &grid) {
    short coor_x, coor_y;
    for (int i=0; i<NUMBER_OF_BOXES; ++i) {
        for (int j=0; j<NUMBER_OF_BOXES; ++j) {
            coor_x = INIT_X + j * DIFFERENCE_X;
            coor_y = INIT_Y + i * DIFFERENCE_Y;
            grid [i][j].setCoordinates (coor_y, coor_x);
        }
    }
}

/**
 * Print the data of the boxes.
 *
 * @param  array
 * @return void
 */
void printGridData (BOXES &grid) {
    int value;
    COOR pos;
    for (int i=0; i<NUMBER_OF_BOXES; ++i) {
        for (int j=0; j<NUMBER_OF_BOXES; ++j) {
            value = grid [i][j].getValue ();
            pos   = grid [i][j].getCoordinates ();
            if (! grid [i][j].isBlank ()) printMessage (value, pos.second, pos.first);
            else printMessage (" ", pos.second, pos.first);
        }
    }
    printMessage ("", 0, 0);
}

/**
 * Generate random number.
 *
 * @param  array
 * @return pair
 */
COOR generateRandom (BOXES &grid) {
    int randomRow, randomCol;
    while (1) {
        randomRow = rand () % NUMBER_OF_BOXES;
        randomCol = rand () % NUMBER_OF_BOXES;
        if (grid [randomRow][randomCol].isBlank ()) break;
    }
    return { randomRow, randomCol };
}

/**
 * Set the starting of the game.
 *
 * @param  array
 * @return void
 */
void initializeGame (BOXES &grid) {
    for (int i=0; i<2; ++i) {
        short newValue = (rand () % 2 + 1) * 2;
        COOR key = generateRandom (grid);
        COOR pos = grid [key.first][key.second].getCoordinates ();

        grid [key.first][key.second].updateValue (newValue);
        grid [key.first][key.second].fill ();
        printMessage (newValue, pos.second, pos.first);
    }
}

/**
 * Move a box.
 *
 * @param  array
 * @param  pair, pair
 * @param  boolean
 * @return void
 */
void teleportBox (BOXES &grid, COOR &to, COOR &from, bool mergeAllowed) {
    int value = grid [from.first][from.second].getValue ();
    
    grid [from.first][from.second].updateValue (0);
    if (mergeAllowed) value = value * 2;
    grid [to.first][to.second].updateValue (value);
    
    grid [from.first][from.second].empty ();
    grid [to.first][to.second].fill ();
}

/**
 * Control the game when left or right is pressed
 *
 * @param  array
 * @param  enum
 * @return void
 */
void changeGridHorizontally (BOXES &grid, Key key) {

    short free;
    int oldValue;
    bool mergeAllowed;
    int x1   = key == LEFT ? 0 : NUMBER_OF_BOXES-1;
    int x2   = key == LEFT ? NUMBER_OF_BOXES-1 : 0;
    int next = key == LEFT ? 1 : -1;

    for (int i=0; i<NUMBER_OF_BOXES; ++i) {
        free = x1, oldValue = -1;
        for (int j=x1; j!=x2+next; j+=next) {

            if (! grid [i][j].isBlank ()) {
                
                COOR to = {i, free}, from = {i, j};
                if (key == LEFT) {
                    mergeAllowed = free > 0 && oldValue > 0 && grid [i][free-1].getValue () == grid [i][j].getValue ();
                    if (mergeAllowed) to.second = to.second - 1;
                } else if (key == RIGHT) {
                    mergeAllowed = free < NUMBER_OF_BOXES-1 && oldValue > 0 && grid [i][free+1].getValue () == grid [i][j].getValue ();
                    if (mergeAllowed) to.second = to.second + 1;
                }

                teleportBox (grid, to, from, mergeAllowed);
                oldValue = mergeAllowed ? -1 : grid [i][to.second].getValue ();
                free = mergeAllowed ? free : (key == LEFT ? free + 1 : free - 1);
            }
        }
    }
}

/**
 * Control the game when up or down is pressed
 *
 * @param  array
 * @param  enum
 * @return void
 */
void changeGridVertically (BOXES &grid, Key key) {

    short free;
    int oldValue;
    bool mergeAllowed;
    int x1   = key == UP ? 0 : NUMBER_OF_BOXES-1;
    int x2   = key == UP ? NUMBER_OF_BOXES-1 : 0;
    int next = key == UP ? 1 : -1;

    for (int i=0; i<NUMBER_OF_BOXES; ++i) {
        free = x1, oldValue = -1;
        for (int j=x1; j!=x2+next; j+=next) {

            if (! grid [j][i].isBlank ()) {
                
                COOR to = {free, i}, from = {j, i};
                if (key == UP) {
                    mergeAllowed = free > 0 && oldValue > 0 && grid [free-1][i].getValue () == grid [j][i].getValue ();
                    if (mergeAllowed) to.second = to.second - 1;
                } else if (key == DOWN) {
                    mergeAllowed = free < NUMBER_OF_BOXES-1 && oldValue > 0 && grid [free+1][i].getValue () == grid [j][i].getValue ();
                    if (mergeAllowed) to.second = to.second + 1;
                }

                teleportBox (grid, to, from, mergeAllowed);
                oldValue = mergeAllowed ? -1 : grid [to.second][i].getValue ();
                free = mergeAllowed ? free : (key == UP ? free + 1 : free - 1);
            }
        }
    }
}

/**
 * Seed the grid with data for testing.
 *
 * @param  array
 * @return void
 */
void seedGame (BOXES &grid) {
    vector <int> row ({1, 1, 1, 1});
    vector <int> col ({0, 1, 2, 3});
    for (int i=0; i<row.size (); ++i) {
        grid [row [i]][col [i]].updateValue (2);
        grid [row [i]][col [i]].fill ();
    }
    printGridData (grid);
}

/**
 * Controller of the game.
 *
 * @param  array
 * @return void
 */
void playGame (BOXES &grid) {
    char ch;
    do {
        ch = getch ();
        if (ch == 0 || ch == 0xE0) ch = getche ();
        if (ch == 75) changeGridHorizontally (grid, LEFT);
        else if (ch == 77) changeGridHorizontally (grid, RIGHT);
        else if (ch == 72) changeGridVertically (grid, UP);
        else if (ch == 80) changeGridVertically (grid, DOWN);
        printGridData (grid);
    } while (ch != 'q' && ch != 'Q' && ch != 27);
}

/**
 * Main function.
 *
 * @param  void
 * @return int
 */
int main () {
    srand (time (NULL));
    BOXES grid (NUMBER_OF_BOXES, vector <Box> (NUMBER_OF_BOXES));
    assignCoordinates (grid);
    initializeScreen ();
    initializeGame (grid);
    playGame (grid);
    printMessage ("", 0, getMaxCoor ().first);
    return 0;
}
