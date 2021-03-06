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
 *      22OCT2021 ED-008: Added ScoreToken functionality
 *      26OCT2021 ED-015: Change value types to floats
 *      27OCT2021 ED-021: Set origin to center
 **/

#ifndef UNICORN_H
#define UNICORN_H

#include "creature.h"

class Unicorn: public Creature{
public:
    Unicorn(float xDim, float yDim, float x, float y):Creature(xDim, yDim, x, y){initUnicorn();}
    void initUnicorn()
    {
        setTextureAndSprite("graphics/angry_unicorn.png");
        struct ScoreToken unicornToken;
        unicornToken.points = 0;
        unicornToken.lives = 1;
        setToken(unicornToken);
        setAlive(true);
        setOriginCenter();
        setCreatureID("Unicorn");
    }
private:
    int test;
};

#endif