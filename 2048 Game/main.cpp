#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include "class.h"
#include "console.h"
#include "display.h"
#include "config.h"

enum Key { UP, RIGHT, DOWN, LEFT };  /* Codes of the keys pressed */
bool CHANGE = false;  /* Counter of a change on a move */
bool WINNER = false;  /* Winner counter */
bool GAME_END = false;  /* Game over counter */
int TILES_FILLED = 0;  /* Number of tiles filled */
using namespace std;

/**
 * Get the max limit of x and y coordinates
 *
 * @param  int
 * @return pair
 */
COOR getMaxCoor (short skip = 0) {
    return {
        INIT_Y + skip + DIFFERENCE_Y * NUMBER_OF_BOXES,  /* maximum point on y-axis */
        INIT_X + skip + DIFFERENCE_X * NUMBER_OF_BOXES   /* maximum point on x-axis */
    };
}

/**
 * Print game over message.
 *
 * @param  void
 * @return void
 */
void printGameOverMessage (bool status) {
    if (status) {
        printMessage ("Congratulations! You have won the game.", 2, getMaxCoor ().first);
    } else {
        printMessage ("Sorry! You lost the game.              ", 2, getMaxCoor ().first);
    }
}

/**
 * Set up the initial screen.
 *
 * @param  void
 * @return void
 */
void initializeScreen () {

    /* Draw borders and heading */
    setConsoleSize (600, 600);
    printCharacters ('=', 0, getMaxCoor ().second, 0);
    printCharacters ('=', 0, getMaxCoor ().second, 2);
    printMessage ("2048 Game", 2, 1);

    short x1 = INIT_X - DIFFERENCE_X / 2, y,
          x2 = getMaxCoor ().second - DIFFERENCE_X / 2,
          y1 = INIT_Y - DIFFERENCE_Y / 2,
          y2 = getMaxCoor ().first - DIFFERENCE_Y / 2;

    /* Draw vertical borders of the grid */
    for (short x=x1; x<=x2; x+=DIFFERENCE_X) {
        for (short y=y1; y<=y2; ++y) {
            printCharacters ('|', x, x, y);
        }
    }

    /* Draw horizontal borders of the grid */
    for (short i=0; i<=NUMBER_OF_BOXES; ++i) {
        y = y1 + i * DIFFERENCE_Y;
        printCharacters ('=', x1, x2, y);
    }
    printMessage ("Press 'P' to play or 'Q' to quit.", 2, getMaxCoor ().first);
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
            printMessage ("     ", pos.second-2, pos.first);

            if (! grid [i][j].isBlank ()) {
                if (value < 10) printMessage (value, pos.second, pos.first);
                else if (value < 1000) printMessage (value, pos.second-1, pos.first);
                else printMessage (value, pos.second-2, pos.first);
            }
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

    /* Generate random blank box to fill a new value */
    while (1) {
        randomRow = rand () % NUMBER_OF_BOXES;
        randomCol = rand () % NUMBER_OF_BOXES;
        if (grid [randomRow][randomCol].isBlank ()) break;
    }

    /* Return the random box */
    return { randomRow, randomCol };
}

/**
 * Fill a new box.
 *
 * @param  array
 * @return void
 */
void fillNewBox (BOXES &grid) {
    short newValue = (rand () % 2 + 1) * 2;
    COOR key = generateRandom (grid);
    COOR pos = grid [key.first][key.second].getCoordinates ();
    
    /* Set the values of the box */
    grid [key.first][key.second].updateValue (newValue);
    grid [key.first][key.second].fill ();
}

/**
 * Set the starting of the game.
 *
 * @param  array
 * @return boolean
 */
bool initializeGame (BOXES &grid) {
    char ch;
    do {
        ch = getch ();
        if (ch == 0) continue;
    } while (ch != 'q' && ch != 'Q' && ch != 27 && ch != 'p' && ch != 'P');

    /* If the choice is not to play */
    if (ch != 'p' && ch != 'P') return 0;
    
    /* Fill the first two box to start the game */
    for (int i=0; i<2; ++i) fillNewBox (grid);
    printGridData (grid);
    return 1;  /* If the user wants to play */
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
    
    if (to.first == from.first && to.second == from.second) {
        return;
    }
    
    /* A box will change */
    CHANGE = true;

    /* Get the value of the source box */
    int value = grid [from.first][from.second].getValue ();

    /* Update the value of the boxes on a grid move */
    grid [from.first][from.second].updateValue (0);
    if (mergeAllowed) value = value * 2;
    if (value == WINNER_SCORE) WINNER = true;  /* winner score tile reached; Game finished */
    grid [to.first][to.second].updateValue (value);

    /* Empty the source and fill the destination box */
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

    short free;  /* Store the box index to which a non-merging box will move */
    int oldValue;  /* Counter for merging of boxes */
    bool mergeAllowed;  /* Counter for if merging is allowed */
    int x1   = key == LEFT ? 0 : NUMBER_OF_BOXES-1;
    int x2   = key == LEFT ? NUMBER_OF_BOXES-1 : 0;
    int next = key == LEFT ? 1 : -1;

    for (int i=0; i<NUMBER_OF_BOXES; ++i) {
        free = x1, oldValue = -1;
        for (int j=x1; j!=x2+next; j+=next) {

            /* If a box is not empty then move the box */
            if (! grid [i][j].isBlank ()) {

                COOR to = {i, free}, from = {i, j};  /* Source and destination boxes */
                if (key == LEFT) {
                    mergeAllowed = free > 0 && oldValue > 0 && grid [i][free-1].getValue () == grid [i][j].getValue ();
                    if (mergeAllowed) to.second = to.second - 1;
                } else if (key == RIGHT) {
                    mergeAllowed = free < NUMBER_OF_BOXES-1 && oldValue > 0 && grid [i][free+1].getValue () == grid [i][j].getValue ();
                    if (mergeAllowed) to.second = to.second + 1;
                }

                /* Move the box and update the counters */
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

    short free;  /* Store the box index to which a non-merging box will move */
    int oldValue;  /* Counter for merging of boxes */
    bool mergeAllowed;  /* Counter for if merging is allowed */
    int x1   = key == UP ? 0 : NUMBER_OF_BOXES-1;
    int x2   = key == UP ? NUMBER_OF_BOXES-1 : 0;
    int next = key == UP ? 1 : -1;

    for (int i=0; i<NUMBER_OF_BOXES; ++i) {
        free = x1, oldValue = -1;
        for (int j=x1; j!=x2+next; j+=next) {

            /* If a box is not empty then move the box */
            if (! grid [j][i].isBlank ()) {

                COOR to = {free, i}, from = {j, i};  /* Source and destination boxes */
                if (key == UP) {
                    mergeAllowed = free > 0 && oldValue > 0 && grid [free-1][i].getValue () == grid [j][i].getValue ();
                    if (mergeAllowed) to.first = to.first - 1;
                } else if (key == DOWN) {
                    mergeAllowed = free < NUMBER_OF_BOXES-1 && oldValue > 0 && grid [free+1][i].getValue () == grid [j][i].getValue ();
                    if (mergeAllowed) to.first = to.first + 1;
                }

                /* Move the box and update the counters */
                teleportBox (grid, to, from, mergeAllowed);
                oldValue = mergeAllowed ? -1 : grid [to.first][i].getValue ();
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
    vector <int> row ({0, 0, 1, 1});
    vector <int> col ({0, 1, 0, 1});
    vector <int> data ({2, 4, 8, 16});

    /* Fill the grid with dry values */
    for (int i=0; i<row.size (); ++i) {
        grid [row [i] % NUMBER_OF_BOXES][col [i] % NUMBER_OF_BOXES].updateValue (data [i]);
        grid [row [i] % NUMBER_OF_BOXES][col [i] % NUMBER_OF_BOXES].fill ();
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
        CHANGE = false;  /* Change is false before every move */
        if (ch == 0 || ch == 0xE0) ch = getche ();
        if (ch == 75) changeGridHorizontally (grid, LEFT);
        else if (ch == 77) changeGridHorizontally (grid, RIGHT);
        else if (ch == 72) changeGridVertically (grid, UP);
        else if (ch == 80) changeGridVertically (grid, DOWN);
        
        /**
         * Important: True value of CHANGE is important before calling fillNewBox ()
         * When there is no change in grid, there is no need to fill a new tile
         */
        if ((ch == 75 || ch == 77 || ch == 72 || ch == 80) && CHANGE) {
            fillNewBox (grid);
            printGridData (grid);
        }
        
        if (WINNER || GAME_END) {
            if (WINNER) printGameOverMessage (true);
            else printGameOverMessage (false);
            break;
        }
        
    } while (ch != 'q' && ch != 'Q' && ch != 27);
}

/**
 * Main function.
 *
 * @param  void
 * @return int
 */
int main () {
    srand (time (NULL));  /* Delete seed to get random values everytime */
    BOXES grid (NUMBER_OF_BOXES, vector <Box> (NUMBER_OF_BOXES));  /* Create an array of boxes */
    assignCoordinates (grid);  /* Assign the console coordinates to the boxes */
    initializeScreen ();  /* Initialize the screen */
    if (initializeGame (grid)) {  /* Start the game */
       playGame (grid);  /* Control the game */
    }
    printMessage ("Game Over. Thanks for playing.", 2, getMaxCoor (1).first);
    return 0;
}
