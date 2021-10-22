/**
 * Main Class
 * 
 * Author: Raymond Jia
 * Class: ECE 4122 - Hurley
 * Lab 3
 * 
 * Description:
 * 
 * Revision History:
 *      21OCT2021 ED-002: Document Created
 *      21OCT2021 ED-003: Added basic bee
 *      22OCT2021 ED-008: Added bank of targets 
 **/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "bee.h"
#include "unicorn.h"
#include "woodland.h"
#include "evil.h"
#include "targetBank.h"

#define WINDOW_XDIM 1920
#define WINDOW_YDIM 1080

#define START 0
#define PLAYING 1
#define END 2

int gameState;

using namespace sf;

int main(){
    // Create a video mode object
    VideoMode vm(WINDOW_XDIM, WINDOW_YDIM);
    // Create and open a window for the game
    RenderWindow window(vm, "Buzzy's Revenge!", Style::Default);

    // Create a texture to hold a graphic on the GPU
    Texture textureBackground;
    // Load a graphic into the texture
    textureBackground.loadFromFile("graphics/background.png");
    // Create a sprite
    Sprite spriteBackground;// Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);
    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0, 0);

    Bee flyingBee(60,40,1800,100);
    TargetBank theTargets;

    gameState = START;
    while(window.isOpen())
    {
        /**
         * Check for User Input
         **/
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }


        /**
         * Perform Drawings
         **/
        window.clear();
        window.draw(spriteBackground);
        if(flyingBee.getAlive())
        {
            window.draw(flyingBee.getSpriteCreature());
        }
        for(int i=0; i<theTargets.getCol1Size(); ++i)
        {
            window.draw(theTargets.getColCreature(0,i)->getSpriteCreature());
        }
        for(int i=0; i<theTargets.getCol2Size(); ++i)
        {
            window.draw(theTargets.getColCreature(1,i)->getSpriteCreature());
        }
        if(gameState == START)
        {

        }
        window.display();
    }

    return 0;
}