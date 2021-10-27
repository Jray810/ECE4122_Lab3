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

#include "buzzy.h"
#include <cmath>

#define BIG_G 300
#define PI 3.14159265

void Buzzy::initBuzzy()
{
    setTextureAndSprite("graphics/smallbuzzy.png");
    setAlive(true);
    setCreatureID("Buzzy");
    setOriginCenter();
}

void Buzzy::reset(float xDim, float yDim, float x, float y)
{
    setXDim(xDim);
    setYDim(yDim);
    setXPos(x);
    setYPos(y);
    setAngle(0);
}

void Buzzy::launchBuzzy(float angle, float velocity)
{
    setAngle(angle);
    initV = velocity;
    initV_X = cos(angle*PI/180) * velocity;
    initV_Y = sin(angle*PI/180) * velocity;
}

void Buzzy::updatePosition(float t)
{
    time = t;
    float posX = initV_X * t + initXPos;
    float posY = 0.5 * BIG_G * pow(t, 2) + initV_Y * t + initYPos;
    setPos(posX, posY);
    updateAngle();
}

void Buzzy::updateAngle()
{
    float currentVX = initV_X;
    float currentVY = BIG_G * time + initV_Y;
    float currentAngle = atan2(currentVY, currentVX) * 180 / PI;
    setAngle(currentAngle);
}

float Buzzy::getTipX()
{
    return getXPos() + cos(getAngle()*PI/180) * 0.5 * getXDim();
}

float Buzzy::getTipY()
{
    return getYPos() + sin(getAngle()*PI/180) * 0.5 * getYDim();
}