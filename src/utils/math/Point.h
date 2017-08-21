#ifndef POINT_H
#define POINT_H

struct Point
{
    Point(int x_pos, int y_pos) : x(x_pos), y(y_pos){}; 
    int x;
    int y;
};

#endif