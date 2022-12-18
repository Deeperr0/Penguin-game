#include "structures.h"
Point makePoint(int x, int y){
    Point tmp;
    tmp.x =  x;
    tmp.y = y;
    return tmp;
}
Color makeColor(int red, int green, int blue)
{
    Color temp;
    temp.red = red;
    temp.green = green;
    temp.blue = blue;
    return temp;
}

