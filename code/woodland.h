/**
 * Woodland Class
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

#ifndef WOODLAND_H
#define WOODLAND_H

#include "creature.h"

class Woodland: public Creature{
public:
    Woodland(int xDim, int yDim, int x, int y, std::string name):Creature(xDim, yDim, x, y){initWoodland(name);}
    void initWoodland(std::string name)
    {
        setTextureAndSprite("graphics/" + name + ".png");
        struct ScoreToken woodlandToken;
        woodlandToken.points = 0;
        woodlandToken.lives = -1;
        setToken(woodlandToken);
        setAlive(true);
        setCreatureID(name);
    }
private:
    int test;
};

#endif