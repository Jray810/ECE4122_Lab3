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
 *      26OCT2021 ED-020: Added Buzzy implementation and full base game logic
 **/

#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "bee.h"
#include "targetBank.h"
#include "buzzy.h"

#include <iostream>

#define WINDOW_XDIM 1920
#define WINDOW_YDIM 1080

#define PAUSED 0
#define LAUNCH_PREP 1
#define PLAYING 2
#define INFLIGHT 3

bool hitChecker(float xPos, float yPos);

int gameState;
int score;
int lives;
Bee* flyingBee;
TargetBank* theTargets;
Buzzy* buzzBullet;

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

    Texture textureLife;
    textureLife.loadFromFile("graphics/buzzy life.png");
    Sprite spriteLife;
    spriteLife.setTexture(textureLife);
    spriteLife.setPosition(160,40);

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

    scoreText.setPosition(1700,40);
	livesText.setPosition(40, 40);
    powerText.setPosition(40,980);
//-----------------------------------------------
    RectangleShape powerBarOutline;
    powerBarOutline.setSize(Vector2f(400,40));
    powerBarOutline.setFillColor(Color::Transparent);
    powerBarOutline.setOutlineColor(Color::Black);
    powerBarOutline.setOutlineThickness(5);
    powerBarOutline.setPosition(160, 980);

    RectangleShape powerBar;
    powerBar.setSize(Vector2f(0, 40));
    powerBar.setFillColor(Color::Red);
    powerBar.setPosition(160, 980);

    flyingBee = new Bee(60,40,1500,200);
    buzzBullet = new Buzzy(237,85,40,WINDOW_YDIM / 2.0f);
    theTargets = new TargetBank();
    Clock clock;
    Time timeCheck;

    gameState = PAUSED;

    float initVelocity;
    bool lastSpaceBarHeld;
    while(window.isOpen())
    {
        /**
         * Check for User Input
         **/
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (gameState == PAUSED)
        {
            initVelocity = 0;
            lives = 5;
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                score = 0;
                gameState = LAUNCH_PREP;
                sleep(1);
            }
        }
        else if (gameState == LAUNCH_PREP)
        {
            initVelocity = 0;
            lastSpaceBarHeld = false;
            gameState = PLAYING;
        }
        else if (gameState == PLAYING)
        {
            float newAngle;
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                newAngle = buzzBullet->getAngle()-1 >= -90 || buzzBullet->getAngle()-1 == 0 ? buzzBullet->getAngle()-1 : -90;
                buzzBullet->setAngle(newAngle);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                newAngle = buzzBullet->getAngle()+1 <= 0 ? buzzBullet->getAngle()+1 : 0;
                buzzBullet->setAngle(newAngle);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                initVelocity+=10;
                if (initVelocity > 800)
                {
                    initVelocity = 800;
                }
                lastSpaceBarHeld = true;
            }
            else if (!Keyboard::isKeyPressed(Keyboard::Space) && lastSpaceBarHeld)
            {
                gameState = INFLIGHT;
                buzzBullet->launchBuzzy(buzzBullet->getAngle(), initVelocity);
                clock.restart();
                continue;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                buzzBullet->reset(237,85,40,WINDOW_YDIM / 2.0f);
                theTargets->targetReset();
                gameState = PAUSED;
                sleep(1);
            }
        }
        else if (gameState == INFLIGHT)
        {
            timeCheck = clock.getElapsedTime();
            buzzBullet->updatePosition(timeCheck.asSeconds());
            if (hitChecker(buzzBullet->getXPos(), buzzBullet->getYPos()))
            {
                buzzBullet->reset(237,85,40,WINDOW_YDIM / 2.0f);
                gameState = LAUNCH_PREP;
                if (!theTargets->refresh())
                {
                    theTargets->targetReset();
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                buzzBullet->reset(237,85,40,WINDOW_YDIM / 2.0f);
                gameState = PAUSED;
                sleep(1);
            }
            if (lives < 1)
            {
                theTargets->targetReset();
                gameState = PAUSED;
            }
        }

        /**
         * Perform Drawings
         **/
        window.clear();
        window.draw(spriteBackground);
        if(flyingBee->getAlive())
        {
            window.draw(flyingBee->getSpriteCreature());
        }
        if(buzzBullet->getAlive())
        {
            window.draw(buzzBullet->getSpriteCreature());
        }
        for(int i=0; i<theTargets->getCol1Size(); ++i)
        {
            window.draw(theTargets->getColCreature(0,i)->getSpriteCreature());
        }
        for(int i=0; i<theTargets->getCol2Size(); ++i)
        {
            window.draw(theTargets->getColCreature(1,i)->getSpriteCreature());
        }
	    scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
        window.draw(livesText);
        window.draw(powerText);
        powerBar.setSize(Vector2f(initVelocity/2.0f, 40));
        window.draw(powerBar);
        window.draw(powerBarOutline);
        for (int i=0; i<lives; ++i)
        {
            spriteLife.setPosition(160 + 80 * i, 40);
            window.draw(spriteLife);
        }
        if(gameState == PAUSED)
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
    delete flyingBee;
    delete theTargets;
    delete buzzBullet;
    return 0;
}

bool hitChecker(float xPos, float yPos)
{
    if (buzzBullet->getXPos() > WINDOW_XDIM || buzzBullet->getYPos() > WINDOW_YDIM)
    {
        lives--;
        return true;
    }

    if (flyingBee->isHit(xPos, yPos))
    {
        score += flyingBee->getToken().points;
        return true;
    }

    for (int i=0; i<theTargets->getCol1Size(); ++i)
    {
        if (theTargets->getColCreature(0,i)->isHit(xPos, yPos))
        {
            score += theTargets->getColCreature(0,i)->getToken().points;
            lives += theTargets->getColCreature(0,i)->getToken().lives;
            return true;
        }
    }

    for (int i=0; i<theTargets->getCol2Size(); ++i)
    {
        if (theTargets->getColCreature(1,i)->isHit(xPos, yPos))
        {
            score += theTargets->getColCreature(1,i)->getToken().points;
            lives += theTargets->getColCreature(1,i)->getToken().lives;
            return true;
        }
    }
    
    return false;
}