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
 *      26OCT2021 ED-015: Change value types to floats
 *      27OCT2021 ED-021: Set origin to center
 **/

#ifndef WOODLAND_H
#define WOODLAND_H

#include "creature.h"

class Woodland: public Creature{
public:
    Woodland(float xDim, float yDim, float x, float y, std::string name):Creature(xDim, yDim, x, y){initWoodland(name);}
    void initWoodland(std::string name)
    {
        setTextureAndSprite("graphics/" + name + ".png");
        struct ScoreToken woodlandToken;
        woodlandToken.points = 0;
        woodlandToken.lives = -1;
        setToken(woodlandToken);
        setAlive(true);
        setOriginCenter();
        setCreatureID(name);
    }
private:
    int test;
};

#endif