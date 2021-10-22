/**
 * Bee Class
 * 
 * Author: Raymond Jia
 * Class: ECE 4122 - Hurley
 * Lab 3
 * 
 * Description:
 * 
 * Revision History:
 *      21OCT2021 ED-003: Document Created
 **/

#ifndef BEE_H
#define BEE_H

#include "creature.h"

class Bee: public Creature{
public:
    Bee(int xDim, int yDim, int x, int y):Creature(xDim, yDim, x, y){initBee();}
    void initBee()
    {
        setTextureAndSprite("graphics/insect.png");
        setPtValue(75);
        setAlive(true);
        setCreatureID("Bee");
    }
private:
    int test;
};

#endif