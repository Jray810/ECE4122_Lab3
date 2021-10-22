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
 *      22OCT2021 ED-011: Added pause screen text
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
int score;
int lives;

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

    score = 0;
    lives = 5;

//------------------------------------------
	Text titleText;
    Text instr1Text;
    Text instr2Text;
    Text instr3Text;
    Text instr4Text;
    Text author1Text;
    Text author2Text;
	Text scoreText;
    Text livesText;
    Text powerText;

	Font boldFont;
	boldFont.loadFromFile("fonts/comicbd.ttf");

    Font regFont;
    regFont.loadFromFile("fonts/comic.ttf");

	titleText.setFont(boldFont);
    instr1Text.setFont(regFont);
    instr2Text.setFont(regFont);
    instr3Text.setFont(regFont);
    instr4Text.setFont(regFont);
    author1Text.setFont(regFont);
    author2Text.setFont(regFont);
	scoreText.setFont(regFont);
    livesText.setFont(regFont);
    powerText.setFont(regFont);

	titleText.setString("Buzzy's Revenge");
    instr1Text.setString("Press Enter to Restart Game");
    instr2Text.setString("Press Esc to exit");
    instr3Text.setString("Press Space to Powerup");
    instr4Text.setString("Press up/down arrow to aim");
    author1Text.setString("created by");
    author2Text.setString("Raymond Jia");
	scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives");
    powerText.setString("Power");

	titleText.setCharacterSize(100);
    instr1Text.setCharacterSize(75);
    instr2Text.setCharacterSize(75);
    instr3Text.setCharacterSize(75);
    instr4Text.setCharacterSize(75);
    author1Text.setCharacterSize(36);
    author2Text.setCharacterSize(36);
	scoreText.setCharacterSize(36);
    livesText.setCharacterSize(36);
    powerText.setCharacterSize(36);

	titleText.setFillColor(Color::Red);
	instr1Text.setFillColor(Color::White);
	instr2Text.setFillColor(Color::White);
	instr3Text.setFillColor(Color::White);
	instr4Text.setFillColor(Color::White);
	author1Text.setFillColor(Color::White);
	author2Text.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);
	livesText.setFillColor(Color::White);
	powerText.setFillColor(Color::White);

	FloatRect titleTextRect = titleText.getLocalBounds();
    FloatRect instr1TextRect = instr1Text.getLocalBounds();
    FloatRect instr2TextRect = instr2Text.getLocalBounds();
    FloatRect instr3TextRect = instr3Text.getLocalBounds();
    FloatRect instr4TextRect = instr4Text.getLocalBounds();
    FloatRect author1TextRect = author1Text.getLocalBounds();
    FloatRect author2TextRect = author2Text.getLocalBounds();

	titleText.setOrigin(titleTextRect.left +
		titleTextRect.width / 2.0f,
		titleTextRect.top +
		titleTextRect.height / 4.0f);

	instr1Text.setOrigin(instr1TextRect.left +
		instr1TextRect.width / 2.0f,
		instr1TextRect.top +
		instr1TextRect.height / 2.0f);

	instr2Text.setOrigin(instr2TextRect.left +
		instr2TextRect.width / 2.0f,
		instr2TextRect.top +
		instr2TextRect.height / 2.0f);

	instr3Text.setOrigin(instr3TextRect.left +
		instr3TextRect.width / 2.0f,
		instr3TextRect.top +
		instr3TextRect.height / 2.0f);

	instr4Text.setOrigin(instr4TextRect.left +
		instr4TextRect.width / 2.0f,
		instr4TextRect.top +
		instr4TextRect.height / 2.0f);

	author1Text.setOrigin(author1TextRect.left +
		author1TextRect.width / 2.0f,
		author1TextRect.top +
		author1TextRect.height / 2.0f);

	author2Text.setOrigin(author2TextRect.left +
		author2TextRect.width / 2.0f,
		author2TextRect.top +
		author2TextRect.height / 2.0f);

	titleText.setPosition(WINDOW_XDIM / 2.0f, WINDOW_YDIM / 5.0f);
	instr1Text.setPosition(WINDOW_XDIM / 2.0f, WINDOW_YDIM / 2.0f - 112);
	instr2Text.setPosition(WINDOW_XDIM / 2.0f, WINDOW_YDIM / 2.0f - 37);
	instr3Text.setPosition(WINDOW_XDIM / 2.0f, WINDOW_YDIM / 2.0f + 38);
	instr4Text.setPosition(WINDOW_XDIM / 2.0f, WINDOW_YDIM / 2.0f + 113);
	author1Text.setPosition(WINDOW_XDIM / 2.0f, WINDOW_YDIM * 3 / 4.0f);
	author2Text.setPosition(WINDOW_XDIM / 2.0f, WINDOW_YDIM * 3 / 4.0f + 38);

    scoreText.setPosition(1740,40);
	livesText.setPosition(40, 40);
    powerText.setPosition(40,980);
//-----------------------------------------------

    Bee flyingBee(60,40,1500,200);
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
        window.draw(scoreText);
        window.draw(livesText);
        window.draw(powerText);
        if(gameState == START)
        {
            window.draw(titleText);
            window.draw(instr1Text);
            window.draw(instr2Text);
            window.draw(instr3Text);
            window.draw(instr4Text);
            window.draw(author1Text);
            window.draw(author2Text);
        }
        window.display();
    }

    return 0;
}