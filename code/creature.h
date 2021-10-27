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
 *      22OCT2021 ED-009: Removed iostream include and cout commands
 *      24OCT2021 ED-013: Added hit detection
 *      26OCT2021 ED-014: Added rotation handling
 *      26OCT2021 ED-015: Change value types to floats
 *      26OCT2021 ED-016: Added angle handling and setOriginCenter
 *      27OCT2021 ED-021: Adjusted isHit to account for origin at center
 **/

#ifndef CREATURE_H
#define CREATURE_H

#include <SFML/Graphics.hpp>
#include <string>

struct ScoreToken
{
    int lives;
    int points;
};

class Creature
{
public:
    Creature(float xDimension, float yDimension, float x, float y):
        xDim(xDimension),yDim(yDimension),xPos(x),yPos(y){setPos(x,y);}
    Creature(float xDimension, float yDimension, float x, float y, std::string ID):
        xDim(xDimension),yDim(yDimension),xPos(x),yPos(y),creatureID(ID){setPos(x,y); setTextureAndSprite(ID);}

    bool isHit(float x, float y)
    {
        if (alive && x > xPos - xDim/2 && x < xPos + xDim/2 && y > yPos - yDim/2 && y < yPos + yDim/2)
        {
            alive = false;
            return true;
        }
        return false;
    }

    // Setters
    void setXDim(float val){xDim = val;}
    void setYDim(float val){yDim = val;}
    void setXPos(float val){xPos = val; spriteCreature.setPosition(xPos,yPos);}
    void setYPos(float val){yPos = val; spriteCreature.setPosition(xPos,yPos);}
    void setPos(float x, float y){xPos = x; yPos = y; spriteCreature.setPosition(x,y);}
    void setAngle(float val)
    {
        angle = val;
        spriteCreature.setRotation(angle);
    }
    void setAlive(bool val){alive = val;}
    void setCreatureID(std::string name){creatureID = name;}
    void setTextureAndSprite(std::string filePath)
    {
        textureCreature.loadFromFile(filePath);
        spriteCreature.setTexture(textureCreature);
        spriteCreature.setPosition(xPos, yPos);
    }
    void setToken(ScoreToken val){token = val;}
    void setOriginCenter()
    {
        spriteCreature.setOrigin(xDim * 0.5, yDim * 0.5);
    }

    // Getters
    float getXDim(){return xDim;}
    float getYDim(){return yDim;}
    float getXBoundMin(){return xPos;}
    float getXBoundMax(){return xPos + xDim;}
    float getYBoundMin(){return yPos;}
    float getYBoundMax(){return yPos + yDim;}
    float getXPos(){return xPos;}
    float getYPos(){return yPos;}
    float getAngle(){return angle;}
    bool getAlive(){return alive;}
    std::string getCreatureID(){return creatureID;}
    sf::Texture getTextureCreature(){return textureCreature;}
    sf::Sprite getSpriteCreature(){return spriteCreature;}
    ScoreToken getToken(){return token;}

private:
    float xDim;
    float yDim;
    float xPos;
    float yPos;
    float angle;
    bool alive;
    std::string creatureID;
    sf::Texture textureCreature;
    sf::Sprite spriteCreature;
    ScoreToken token;
};

#endif