#include <iostream>


/* Struct example */
struct Point {
    int x;
    int y;
};

struct PolarCoordinate {
    int radius;     // in degrees
    int angle;
};


/* Defining a struct as a type */
typedef struct Point CartesianCoordinate;

typedef struct PolarCoordinate PolarCoordinate;


/* Defining directly */
typedef struct Datetime
{
    /* data */
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} Datetime;


/**
 * MAIN
*/
int main() {

    /* struct */
    struct Point pt;
    pt.x = 1;
    pt.y = 2;
    std::cout << "My point is: (" << pt.x << ", " << pt.y << ").\n";

    /* typedef struct */
    CartesianCoordinate coordC;
    coordC.x = 3;
    coordC.y = 4;
    std::cout << "Cartesian coordinate: x = " << coordC.x << ", y = " << coordC.y << ".\n";

    PolarCoordinate coordP;
    coordP.radius = 5.0;
    coordP.angle = 53; //°
    std::cout << "Polar coordinate: r = " << coordP.radius << ", a = " << coordP.angle << "°.\n";

    /* typedef */
    Datetime dt;
    dt.year = 2022;
    dt.month = 12;
    dt.day = 5;
    dt.hour = 13;
    dt.minute = 34;
    dt.second = 50;
    std::cout << "Datetime: " ;
    std::cout << dt.year << "-" << dt.month << "-" << dt.day << " ";
    std::cout << dt.hour << ":" << dt.minute << ":" << dt.second;

    return 0;
}
