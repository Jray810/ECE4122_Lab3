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
 *      26OCT2021 ED-015: Change value types to floats
 *      27OCT2021 ED-021: Set origin to center
 **/

#ifndef BEE_H
#define BEE_H

#include "creature.h"
#include <stdlib.h>
#include <time.h>

class Bee: public Creature
{
public:
    Bee(float xDim, float yDim, float x, float y):Creature(xDim, yDim, x, y){initBee();}
    void initBee()
    {
        setTextureAndSprite("graphics/insect.png");
        struct ScoreToken beeToken;
        beeToken.points = 75;
        beeToken.lives = 0;
        setToken(beeToken);
        setAlive(true);
        setOriginCenter();
        setCreatureID("Bee");
        srand(time(NULL));
    }
    void reset()
    {
        setAlive(true);
        setPos(1800, 200);
    }
    void updatePosition()
    {
        if (!getAlive())
        {
            return;
        }

        int dir = rand() % 5 - 2;
        if (getXPos() - 1 < 50)
        {
            reset();
            return;
        }
        else
        {
            setXPos(getXPos() - 1);
        }

        if (getYPos() + dir > 300)
        {
            setYPos(300);
        }
        else if (getYPos() + dir < 100)
        {
            setYPos(100);
        }
        else
        {
            setYPos(getYPos() + dir);
        }
    }
private:
    int test;
};

#endif