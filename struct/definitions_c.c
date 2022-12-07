#include <stdio.h>


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
    printf("My point is: (%d, %d).\n", pt.x, pt.y);

    /* typedef struct */
    CartesianCoordinate coordC;
    coordC.x = 3;
    coordC.y = 4;
    printf("Cartesian coordinate: x = %d, y = %d.\n", coordC.x, coordC.y);

    PolarCoordinate coordP;
    coordP.radius = 5.0;
    coordP.angle = 53; //°
    printf("Polar coordinate: r = %d, a = %d%c.\n", coordP.radius, coordP.angle, 248);

    /* typedef */
    Datetime dt;
    dt.year = 2022;
    dt.month = 12;
    dt.day = 5;
    dt.hour = 13;
    dt.minute = 34;
    dt.second = 50;

    printf("Datetime: %04d-%02d-%02d %02d:%02d:%02d\n",
        dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);

    return 0;
}
