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
        struct ScoreToken unicornToken;
        unicornToken.points = 0;
        unicornToken.lives = 1;
        setToken(unicornToken);
        setAlive(true);
        setCreatureID("Unicorn");
    }
private:
    int test;
};

#endif