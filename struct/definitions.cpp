#include <iostream>     // std::cout, std::endl
#include <iomanip>      // std::setfill, std::setw


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
typedef Point CartesianCoordinate;


/* Defining directly */
struct Datetime
{
    /* data */
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};


/**
 * MAIN
*/
int main() {

    /* struct */
    Point pt;
    pt.x = 1;
    pt.y = 2;
    std::cout << "My point is: (" << pt.x << ", " << pt.y << ")." << std::endl;

    /* typedef struct */
    CartesianCoordinate coordC;
    coordC.x = 3;
    coordC.y = 4;
    std::cout << "Cartesian coordinate: x = " << coordC.x << ", y = " << coordC.y << "." << std::endl;

    PolarCoordinate coordP;
    coordP.radius = 5.0;
    coordP.angle = 53; //°
    std::cout << "Polar coordinate: r = " << coordP.radius << ", a = " << coordP.angle << "°." << std::endl;

    /* typedef */
    Datetime dt;
    dt.year = 2022;
    dt.month = 12;
    dt.day = 5;
    dt.hour = 13;
    dt.minute = 34;
    dt.second = 50;
    std::cout << "Datetime: " ;
    std::cout << dt.year << "-" ;
    std::cout << std::setw(2) << std::setfill('0') << dt.month << "-" ;
    std::cout << std::setw(2) << std::setfill('0') << dt.day << " ";
    std::cout << std::setw(2) << std::setfill('0') << dt.hour << ":" ;
    std::cout << std::setw(2) << std::setfill('0') << dt.minute << ":";
    std::cout << std::setw(2) << std::setfill('0') << dt.second;

    return 0;
}
