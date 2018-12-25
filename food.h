#include "rectangle.h"
#include <time.h>
#ifndef FOOD_H
#define FOOD_H

class Food
{
private:
    Rectangle foodrect;
    int x;
    int y;
public:
    Food():
        foodrect(1,1,.5,.6,.7),
        x(15),
        y(15)
    {}

    void draw()
    {
        foodrect.setposition(x,y);
        foodrect.draw();
    }

    int getx()
    {
        return x;
    }
    int gety()
    {
        return y;
    }

    void randxy()
    {
        srand(clock());
        x=rand()%24+3;
        y=rand()%24+3;
    }
};

#endif