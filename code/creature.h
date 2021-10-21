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
    double getXPos(){return xPos;}
    double getYPos(){return yPos;}
    sf::Texture getTextureCreature(){return textureCreature;}
    sf::Sprite getSpriteCreature(){return spriteCreature;}

private:
    int xDim;
    int yDim;
    int xPos;
    int yPos;
    sf::Texture textureCreature;
    sf::Sprite spriteCreature;
};

#endif