#include <iostream>
#define COOR std::pair<short,short>

/**
 * Store data for each box of the game.
 */
class Box {
    short x, y;
    int value;
    bool filled;
    public:
        Box ();
        COOR getCoordinates () { return {y, x}; }
        int getValue () { return value; }
        bool isBlank () { return !filled; }
        
        void setCoordinates (short, short);
        void updateValue (int data) { value = data; }
        void empty () { filled = false; }
        void fill () { filled = true; }
};

/**
 * Constructor to set initial values
 *
 * @param  void
 * @return void
 */
Box::Box () {
    value = 0;
    filled = false;
}

/**
 * Set the coordinates for the boxes.
 *
 * @param  int, int
 * @return void
 */
void Box::setCoordinates (short i, short j) {
    y = i, x = j;
}
