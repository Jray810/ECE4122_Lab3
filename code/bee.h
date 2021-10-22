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
 *      22OCT2021 ED-008: Added ScoreToken functionality
 **/

#ifndef BEE_H
#define BEE_H

#include "creature.h"

class Bee: public Creature
{
public:
    Bee(int xDim, int yDim, int x, int y):Creature(xDim, yDim, x, y){initBee();}
    void initBee()
    {
        setTextureAndSprite("graphics/insect.png");
        struct ScoreToken beeToken;
        beeToken.points = 75;
        beeToken.lives = 0;
        setToken(beeToken);
        setAlive(true);
        setCreatureID("Bee");
    }
private:
    int test;
};

#endif