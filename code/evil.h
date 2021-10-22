/**
 * Evil Class
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

#ifndef EVIL_H
#define EVIL_H

#include "creature.h"

class Evil: public Creature{
public:
    Evil(int xDim, int yDim, int x, int y, std::string name):Creature(xDim, yDim, x, y){initEvil(name);}
    void initEvil(std::string name)
    {
        setTextureAndSprite("graphics/" + name + ".png");
        struct ScoreToken evilToken;
        evilToken.points = 25;
        evilToken.lives = 0;
        setToken(evilToken);
        setAlive(true);
        setCreatureID(name);
    }
private:
    int test;
};

#endif