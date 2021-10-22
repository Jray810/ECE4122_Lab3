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
 **/

#include <SFML/Graphics.hpp>
#include "bee.h"
#include "unicorn.h"
#include "woodland.h"
#include "evil.h"

using namespace sf;

int main(){
    // Create a video mode object
    VideoMode vm(1920, 1080);
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
    Bee flyingBee(60,40,100,100);
    Unicorn madUnicorn(133,96,200,200);
    Woodland woodlandFrog(98,96,300,300,"frog");
    Evil evilTiger(872,917,400,400,"tiger");
    while(window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        window.clear();
        window.draw(spriteBackground);
        window.draw(flyingBee.getSpriteCreature());
        window.draw(madUnicorn.getSpriteCreature());
        window.draw(woodlandFrog.getSpriteCreature());
        window.draw(evilTiger.getSpriteCreature());
        window.display();
    }

    return 0;
}