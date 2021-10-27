/**
 * Buzzy Class
 * 
 * Author: Raymond Jia
 * Class: ECE 4122 - Hurley
 * Lab 3
 * 
 * Description:
 * 
 * Revision History:
 *      26OCT2021 ED-017: Document Created
 **/

#ifndef BUZZY_H
#define BUZZY_H

#include "creature.h"

class Buzzy: public Creature
{
public:
    Buzzy(float xDim, float yDim, float x, float y): Creature(xDim, yDim, x, y){initXPos = x; initYPos = y; initBuzzy();}

    void initBuzzy();
    void reset(float xDim, float yDim, float x, float y);
    void launchBuzzy(float angle, float velocity);
    void updatePosition(float t);
    void updateAngle();
    float getTipX();
    float getTipY();

    // Setters
    void setInitialVelocity(float val){initV = val;}
    void setInitialVelocityX(float val){initV_X = val;}
    void setInitialVelocityY(float val){initV_Y = val;}
    void setTimeElapsed(float val){time = val;}

    // Getters
    float getInitialVelocity(){return initV;}
    float getinitialVelocityX(){return initV_X;}
    float getinitialVelocityY(){return initV_Y;}
    float getTimeElapsed(){return time;}

private:
    float initV;
    float initV_X;
    float initV_Y;
    float initXPos;
    float initYPos;
    float time;
};

#endif