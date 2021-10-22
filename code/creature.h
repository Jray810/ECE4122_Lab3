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
 *      22OCT2021 ED-008: Added ScoreToken struct and fixed position bugs
 **/

#ifndef CREATURE_H
#define CREATURE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

struct ScoreToken
{
    int lives;
    int points;
};

class Creature
{
public:
    Creature(int xDimension, int yDimension, int x, int y):
        xDim(xDimension),yDim(yDimension),xPos(x),yPos(y){setPos(x,y);}
    Creature(int xDimension, int yDimension, int x, int y, std::string ID):
        xDim(xDimension),yDim(yDimension),xPos(x),yPos(y),creatureID(ID){setPos(x,y); setTextureAndSprite(ID);}

    // Setters
    void setXDim(int val){xDim = val;}
    void setYDim(int val){yDim = val;}
    void setXPos(int val){xPos = val; spriteCreature.setPosition(xPos,yPos);}
    void setYPos(int val){yPos = val; spriteCreature.setPosition(xPos,yPos);}
    void setPos(int x, int y){xPos = x; yPos = y; spriteCreature.setPosition(x,y);}
    void setAlive(bool val){alive = val;}
    void setCreatureID(std::string name){creatureID = name;}
    void setTextureAndSprite(std::string filePath)
    {
        std::cout<<filePath<<std::endl;
        textureCreature.loadFromFile(filePath);
        spriteCreature.setTexture(textureCreature);
        spriteCreature.setPosition(xPos, yPos);
    }
    void setToken(ScoreToken val){token = val;}

    // Getters
    int getXDim(){return xDim;}
    int getYDim(){return yDim;}
    int getXBoundMin(){return xPos;}
    int getXBoundMax(){return xPos + xDim;}
    int getYBoundMin(){return yPos;}
    int getYBoundMax(){return yPos + yDim;}
    int getXPos(){return xPos;}
    int getYPos(){return yPos;}
    bool getAlive(){return alive;}
    std::string getCreatureID(){return creatureID;}
    sf::Texture getTextureCreature(){return textureCreature;}
    sf::Sprite getSpriteCreature(){return spriteCreature;}
    ScoreToken getToken(){return token;}

private:
    int xDim;
    int yDim;
    int xPos;
    int yPos;
    bool alive;
    std::string creatureID;
    sf::Texture textureCreature;
    sf::Sprite spriteCreature;
    ScoreToken token;
};

#endif