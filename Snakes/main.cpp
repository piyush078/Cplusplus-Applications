#include <iostream>
#include <queue>
#include <map>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "console.h"
#include "config.h"
#include "display.h"
using namespace std;

/**
 * Global variables.
 * Prototypes of the functions declared.
 */
queue <COORD> Snake;  /* SNAKE as a queue of the coordinates */
map <COORD, bool> Covered;  /* Store the points under the snake */
COORD Food;  /* Coordinates of the food */
enum Direction { UP, RIGHT, DOWN, LEFT };

COORD generateFood (void);

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
 * Show the new food on the console and handle its coordinates.
 *
 * @param  void
 * @return void
 */
void printNewFood () {
    COORD point = generateFood ();
    consoleLog ('o', point.first, point.second);
    Food = point;
}

/**
 * Generate random point on the console.
 *
 * @param  void
 * @return void
 */
COORD generateFood () {
    short randomRow, randomCol;
    while (1) {
        randomCol = rand () % (_RIGHT_LIMIT - _LEFT_LIMIT - 3) + _LEFT_LIMIT + 1;
        randomRow = rand () % (_BOTTOM_LIMIT - _TOP_LIMIT - 3) + _TOP_LIMIT + 1;
        
        /* If the point is not already under the snake */
        if (Covered.find ({ randomCol, randomRow }) == Covered.end ())
            break;
    }
    return Food = { randomCol, randomRow };
}

/**
 * Set the initial screen and snake in the game.
 *
 * @param  void
 * @return struct
 */
COORD initializeGame () {
    clearConsole ();
    printBoundaries ({ _LEFT_LIMIT, _TOP_LIMIT }, { _RIGHT_LIMIT, _BOTTOM_LIMIT });
    consoleLog ("Use arrow keys to operate", _LEFT_LIMIT, _RIGHT_LIMIT, _BOTTOM_LIMIT + 2);
    
    /* Make the initial snake */
    short x;
    short y = _BOTTOM_LIMIT - 2;
    for (short i=0; i<=4; ++i) {
        x = _RIGHT_LIMIT - i - 2;
        Covered [{x, y}] = true;  /* Put the points under snake in the map */
        Snake.push ({ x, y });  /*  Add new points to the snake */
        consoleLog ('o', x, y);  /* Print snake at the points */
    }
    consoleLog ('<', x, y);  /* Draw the head of the snake */
    return { x, y };
}

/**
 * Check if the food coordinate is covered by the snake.
 *
 * @param  struct
 * @return boolean
 */
bool isFoodEaten (COORD currentPos) {
    return currentPos == Food;
}

/**
 * Push new points and delete the tail in the snake; Print the snake.
 *
 * @param  struct, struct
 * @param  int
 * @param  bool
 * @return void
 */
void slither (COORD newHead, COORD prevHead, int currentDir, bool deleteTail = true) {
    
    /* Remove the previous head */
    consoleLog ('o', prevHead.first, prevHead.second);

    /* It equals false when the length of snake is increased after eating food */
    if (deleteTail) {
        
        /* Delete the tail */
        COORD tail = Snake.front ();
        Snake.pop ();
        consoleLog (' ', tail.first, tail.second);
        Covered.erase ({ tail.first, tail.second });
    }
    
    /* Show the new head and push it in the snake */
    switch (currentDir) {
        case UP: consoleLog ('^', newHead.first, newHead.second); break;
        case LEFT: consoleLog ('<', newHead.first, newHead.second); break;
        case RIGHT: consoleLog ('>', newHead.first, newHead.second); break;
        case DOWN: consoleLog ('v', newHead.first, newHead.second); break;
    }
    Snake.push (newHead);
    Covered [{ newHead.first, newHead.second }] = true;  /* Add the new point to the map */
}

/**
 * Check if a change in the direction is needed.
 *
 * @param  char
 * @param  array
 * @param  int
 * @param  struct
 * @return struct
 */
COORD changeInDirection (char ch, COORD Transition [], int &currentDir, COORD currentPos) {

    int newDirection = -1;  /* Variable for the new direction */
    
    /* Get the new direction */
    if (ch == 75 && currentDir != LEFT && currentDir != RIGHT) newDirection = LEFT;
    else if (ch == 77 && currentDir != LEFT && currentDir != RIGHT) newDirection = RIGHT;
    else if (ch == 72 && currentDir != UP && currentDir != DOWN) newDirection = UP;
    else if (ch == 80 && currentDir != UP && currentDir != DOWN) newDirection = DOWN;
    
    /**
     * Important: Send new coordinates when there is a change in the direction
     * Otherwise send back the same values
     */
    if (newDirection != -1) {
        currentDir = newDirection;  /* Copy new direction to the snake direction */
        return {
            currentPos.first + Transition [newDirection].first,
            currentPos.second + Transition [newDirection].second
        };
    } else {
        return currentPos;
    }
}

/**
 * Operate snake when it continues in the same direction.
 *
 * @param  array
 * @param  int
 * @param  struct
 * @return struct
 */
COORD continuePath (COORD Transition [], int currentDir, COORD currentPos) {
    
    /* Return the new head */
    return {
        currentPos.first + Transition [currentDir].first,
        currentPos.second + Transition [currentDir].second
    };
}

/**
 * Controller of the game.
 *
 * @param  struct
 * @return void
 */
void playGame (COORD currentPos) {

    char ch;
    COORD Transition [4] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };  /* Changes in the coordinates of every direction */
    COORD prevHead;  /* Head of the snake before a move */
    
    /**
     * Current direction of the snake
     * Important: Initial direction is left
     */
    int currentDir = LEFT;
    printNewFood ();  /* Print new food */
    
    do {
        Sleep (1000 / _SPEED);  /* Wait before every snake move */
        prevHead = currentPos;
        
        if (kbhit ()) {
            ch = getch ();
            if (ch == 0 || ch == 0xE0) ch = getche ();
            
            /* If an arrow key is pressed */
            if (ch == 75 || ch == 77 || ch == 72 || ch == 80) {
                currentPos = changeInDirection (ch, Transition, currentDir, currentPos);
            }
        }
        
        /**
         * If the direction has not changed, snake will continue in its current direction
         * If direction is same, prevHead will be same as the currentHead until this line
         */
        if (currentPos == prevHead) {
            currentPos = continuePath (Transition, currentDir, currentPos);
        }
        
        /* Check if the food has been eaten */
        if (isFoodEaten (currentPos)) {
            slither (currentPos, Food, currentDir, false);  /* Make the new head at food coordinates */
            printNewFood ();  /* Print new food */
        }
        
        /* Print the new head and delete the tail */
        slither (currentPos, prevHead, currentDir);
        
    } while (ch != 'q' && ch != 'Q' && ch != 27);
    consoleLog ("Game Over.", _LEFT_LIMIT, _RIGHT_LIMIT, _BOTTOM_LIMIT + 1);
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
        playGame (initializeGame ());
    }
    consoleLog (' ', 0, _BOTTOM_LIMIT+2);
    return 0;
}
