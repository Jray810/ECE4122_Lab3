/**
 * Creature Class
 * 
 * Author: Raymond Jia
 * Class: ECE 4122 - Hurley
 * Lab 3
 * 
 * Description:
 * 
 * Revision History:
 *      21OCT2021 ED-002: Document Created
 **/

#ifndef CREATURE_H
#define CREATURE_H

#include <SFML/Graphics.hpp>
#include <string>

class Creature{
public:
    Creature(int xDimension, int yDimension, int x, int y):
        xDim(xDimension),yDim(yDimension),xPos(x),yPos(y){}

    // Setters
    void setXDim(int val){xDim = val;}
    void setYDim(int val){yDim = val;}
    void setXPos(int val){xPos = val;}
    void setYPos(int val){yPos = val;}
    void setPtValue(int val){ptValue = val;}
    void setAlive(bool val){alive = val;}
    void setCreatureID(std::string name){creatureID = name;}
    void setTextureAndSprite(std::string filePath)
    {
        textureCreature.loadFromFile(filePath);
        spriteCreature.setTexture(textureCreature);
        spriteCreature.setPosition(xPos, yPos);
    }

    // Getters
    int getXDim(){return xDim;}
    int getYDim(){return yDim;}
    int getXBoundMin(){return xPos;}
    int getXBoundMax(){return xPos + xDim;}
    int getYBoundMin(){return yPos;}
    int getYBoundMax(){return yPos + yDim;}
    int getXPos(){return xPos;}
    int getYPos(){return yPos;}
    int getPtValue(){return ptValue;}
    bool getAlive(){return alive;}
    std::string getCreatureID(){return creatureID;}
    sf::Texture getTextureCreature(){return textureCreature;}
    sf::Sprite getSpriteCreature(){return spriteCreature;}

private:
    int xDim;
    int yDim;
    int xPos;
    int yPos;
    int ptValue;
    bool alive;
    std::string creatureID;
    sf::Texture textureCreature;
    sf::Sprite spriteCreature;
};

#endif