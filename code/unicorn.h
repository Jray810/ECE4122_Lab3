/**
 * Unicorn Class
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

#ifndef UNICORN_H
#define UNICORN_H

#include "creature.h"

class Unicorn: public Creature{
public:
    Unicorn(int xDim, int yDim, int x, int y):Creature(xDim, yDim, x, y){initUnicorn();}
    void initUnicorn()
    {
        setTextureAndSprite("graphics/angry_unicorn.png");
        setPtValue(0);
        setAlive(true);
        setCreatureID("Unicorn");
    }
private:
    int test;
};

#endif