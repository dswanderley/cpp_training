#include <iostream>     // std::cout, std::endl
#include <iomanip>      // std::setfill, std::setw


/* Struct example */
struct Point {
    int x;
    int y;
};


/**
 * MAIN
*/
int main() {

    /* pointer to struct */
    Point *ptPtr = new Point;
    ptPtr->x = 1;
    ptPtr->y = 2;
    std::cout << "My point is: (" << ptPtr->x << ", " << ptPtr->y << ").\n";

    /* Array (pointer) of structs */
    int len = 10;
    Point *arr = new Point[len]();

    // Changing one value
    arr[4].x = 5;
    arr[4].y = 1;

    // Show
    for (int i=0; i<len; i++) {
        std::cout << "Point " << std::setw(2) << std::setfill(' ') << i+1;
        std::cout << ": x = " << arr[i].x << ", y = " << arr[i].y << std::endl;
    }

    return 0;
}
