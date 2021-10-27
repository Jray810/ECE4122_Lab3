/**
 * Main
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
 *      27OCT2021 ED-022: Cleaned up Text initialization, added extra credit
 *                        animation functionality
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
#define B_FALLING 4
#define C_FALLING 5
#define RESETTING 6

#define H_BLANK 0
#define H_WOODLAND 1
#define H_EVIL 2
#define H_OTHER 3

int hitChecker(float xPos, float yPos);
void initializeTitles(int window_xDim, int window_yDim);

int gameState;
int score;
int lives;
Bee* flyingBee;
TargetBank* theTargets;
Buzzy* buzzBullet;
sf::Font boldFont;
sf::Font regFont;
sf::Text scoreText("Score: ", regFont, 36);
sf::Text livesText("Lives", regFont, 36);
sf::Text powerText("Power", regFont, 36);
sf::Text titleText("Buzzy's Revenge", boldFont, 100);
sf::Text instr1Text("Press Enter to Restart Game", regFont, 75);
sf::Text instr2Text("Press Esc to exit", regFont, 75);
sf::Text instr3Text("Press Space to Powerup", regFont, 75);
sf::Text instr4Text("Press up/down arrow to aim", regFont, 75);
sf::Text author1Text("created by", regFont, 36);
sf::Text author2Text("Raymond Jia", regFont, 36);

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
    boldFont.loadFromFile("fonts/comicbd.ttf");
    regFont.loadFromFile("fonts/comic.ttf");

    initializeTitles(WINDOW_XDIM, WINDOW_YDIM);

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

    flyingBee = new Bee(100,67,1800,200);
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
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                score = 0;
                gameState = LAUNCH_PREP;
                sleep(1);
            }
        }
        else if (gameState == LAUNCH_PREP)
        {
            buzzBullet->reset(237,85,40,WINDOW_YDIM / 2.0f);
            initVelocity = 0;
            lastSpaceBarHeld = false;
            gameState = PLAYING;
        }
        else if (gameState == PLAYING)
        {
            flyingBee->updatePosition();
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
                gameState = RESETTING;
            }
        }
        else if (gameState == INFLIGHT)
        {
            timeCheck = clock.getElapsedTime();
            buzzBullet->updatePosition(timeCheck.asSeconds());
            flyingBee->updatePosition();
            switch (hitChecker(buzzBullet->getXPos(), buzzBullet->getYPos()))
            {
                case H_WOODLAND:
                    theTargets->refresh(WINDOW_YDIM);
                    gameState = B_FALLING;
                    break;
                case H_EVIL:
                    buzzBullet->reset(237,85,40,WINDOW_YDIM / 2.0f);
                    gameState = C_FALLING;
                    break;
                case H_OTHER:
                    theTargets->refresh(WINDOW_YDIM);
                    gameState = LAUNCH_PREP;
                    break;
                default:
                    break;
            }

            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                gameState = RESETTING;
            }

            if (lives < 1)
            {
                gameState = RESETTING;
            }
        }
        else if (gameState == B_FALLING)
        {
            buzzBullet->setYPos(buzzBullet->getYPos()+5);
            buzzBullet->setAngle(buzzBullet->getAngle()+20);
            if (buzzBullet->getYPos() > WINDOW_YDIM)
            {
                gameState = LAUNCH_PREP;
            }

            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                gameState = RESETTING;
            }
        }
        else if (gameState == C_FALLING)
        {
            if (!theTargets->refresh(WINDOW_YDIM))
            {
                if (theTargets->getCol1Size() == 0 && theTargets->getCol2Size() == 0)
                {
                    theTargets->targetReset();
                    if (!flyingBee->getAlive())
                    {
                        flyingBee->reset();
                    }
                }
                gameState = LAUNCH_PREP;
            }

            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                gameState = RESETTING;
            }
        }
        else if (gameState == RESETTING)
        {
            initVelocity = 0;
            lives = 5;
            buzzBullet->reset(237,85,40,WINDOW_YDIM / 2.0f);
            flyingBee->reset();
            theTargets->targetReset();
            gameState = PAUSED;
            sleep(1);
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
        for(int i=0; i<theTargets->getCol1Size(); ++i)
        {
            window.draw(theTargets->getColCreature(0,i)->getSpriteCreature());
        }
        for(int i=0; i<theTargets->getCol2Size(); ++i)
        {
            window.draw(theTargets->getColCreature(1,i)->getSpriteCreature());
        }
        if(buzzBullet->getAlive())
        {
            window.draw(buzzBullet->getSpriteCreature());
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

int hitChecker(float xPos, float yPos)
{
    if (buzzBullet->getXPos() > WINDOW_XDIM || buzzBullet->getYPos() > WINDOW_YDIM)
    {
        lives--;
        return H_OTHER;
    }

    if (flyingBee->isHit(xPos, yPos))
    {
        score += flyingBee->getToken().points;
        return H_OTHER;
    }

    for (int i=0; i<theTargets->getCol1Size(); ++i)
    {
        if (theTargets->getColCreature(0,i)->isHit(xPos, yPos))
        {
            score += theTargets->getColCreature(0,i)->getToken().points;
            lives += theTargets->getColCreature(0,i)->getToken().lives;
            switch (theTargets->getColCreature(0,i)->getToken().lives)
            {
                case -1:
                    return H_WOODLAND;
                case 0:
                    return H_EVIL;
                case 1:
                    return H_OTHER;
            }
        }
    }

    for (int i=0; i<theTargets->getCol2Size(); ++i)
    {
        if (theTargets->getColCreature(1,i)->isHit(xPos, yPos))
        {
            score += theTargets->getColCreature(1,i)->getToken().points;
            lives += theTargets->getColCreature(1,i)->getToken().lives;
            switch (theTargets->getColCreature(1,i)->getToken().lives)
            {
                case -1:
                    return H_WOODLAND;
                case 0:
                    return H_EVIL;
                case 1:
                    return H_OTHER;
            }
        }
    }
    
    return H_BLANK;
}

void initializeTitles(int window_xDim, int window_yDim)
{
    scoreText.setFillColor(Color::White);
    livesText.setFillColor(Color::White);
    powerText.setFillColor(Color::White);
    titleText.setFillColor(Color::Red);
    instr1Text.setFillColor(Color::White);
    instr2Text.setFillColor(Color::White);
    instr3Text.setFillColor(Color::White);
    instr4Text.setFillColor(Color::White);
    author1Text.setFillColor(Color::White);
    author2Text.setFillColor(Color::White);

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
        titleTextRect.height / 2.0f);

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

    scoreText.setPosition(1700,40);
    livesText.setPosition(40, 40);
    powerText.setPosition(40,980);
    titleText.setPosition(window_xDim / 2.0f, window_yDim / 5.0f);
    instr1Text.setPosition(window_xDim / 2.0f, window_yDim / 2.0f - 112);
    instr2Text.setPosition(window_xDim / 2.0f, window_yDim / 2.0f - 37);
    instr3Text.setPosition(window_xDim / 2.0f, window_yDim / 2.0f + 38);
    instr4Text.setPosition(window_xDim / 2.0f, window_yDim / 2.0f + 113);
    author1Text.setPosition(window_xDim / 2.0f, window_yDim * 3 / 4.0f);
    author2Text.setPosition(window_xDim / 2.0f, window_yDim * 3 / 4.0f + 38);
}