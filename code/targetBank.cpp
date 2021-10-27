/**
 * TargetBank Class
 * 
 * Author: Raymond Jia
 * Class: ECE 4122 - Hurley
 * Lab 3
 * 
 * Description:
 * 
 * Revision History:
 *      22OCT2021 ED-008: Document Created
 *      22OCT2021 ED-012: Resized creature images
 *      26OCT2021 ED-019: Added refresh() function
 **/

#include "targetBank.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <random>

using namespace std;

TargetBank::TargetBank()
{
    srand(time(NULL));

    Unicorn* madUnicorn = new Unicorn(200,144,0,0);

    Woodland* woodlandBunny = new Woodland(200,144,0,0,"bunny");
    Woodland* woodlandChicken = new Woodland(200,144,0,0,"chicken");
    Woodland* woodlandDog = new Woodland(200,144,0,0,"dog");
    Woodland* woodlandFrog = new Woodland(200,144,0,0,"frog");
    Woodland* woodlandMouse = new Woodland(200,144,0,0,"mouse");
    Woodland* woodlandPig = new Woodland(200,144,0,0,"pig");
    Woodland* woodlandSheep = new Woodland(200,144,0,0,"sheep");

    Evil* evilTiger = new Evil(200,144,0,0,"tiger");
    Evil* evilBulldog = new Evil(200,144,0,0,"bulldog");

    woodlanders.push_back(madUnicorn);
    woodlanders.push_back(woodlandBunny);
    woodlanders.push_back(woodlandChicken);
    woodlanders.push_back(woodlandDog);
    woodlanders.push_back(woodlandFrog);
    woodlanders.push_back(woodlandMouse);
    woodlanders.push_back(woodlandPig);
    woodlanders.push_back(woodlandSheep);

    evildoers.push_back(evilTiger);
    evildoers.push_back(evilBulldog);

    targetReset();
}

TargetBank::~TargetBank()
{
    col1.clear();
    col2.clear();
    for(int i=0; i<woodlanders.size(); ++i)
    {
        delete woodlanders[i];
    }
    for(int i=0; i<evildoers.size(); ++i)
    {
        delete evildoers[i];
    }
    woodlanders.clear();
    evildoers.clear();
}

void TargetBank::targetReset()
{
    col1.clear();
    col2.clear();

    int col = rand() % 2;
    col1.push_back(evildoers[col]);
    col2.push_back(evildoers[1 - col]);

    shuffle(woodlanders.begin(), woodlanders.end(), default_random_engine(time(NULL)));

    for(int i=0; i<4; ++i)
    {
        col1.push_back(woodlanders[i]);
        col2.push_back(woodlanders[i+4]);
    }

    shuffle(col1.begin(), col1.end(), default_random_engine(time(NULL)));
    shuffle(col2.begin(), col2.end(), default_random_engine(time(NULL)));

    for(int i=0; i<5; ++i)
    {
        col1[i]->setPos(1500, 900 - 144 * i);
        col1[i]->setAlive(true);
        col2[i]->setPos(1700, 900 - 144 * i);
        col2[i]->setAlive(true);
    }
}

bool TargetBank::refresh()
{
    if (col1.size() > 0)
    {
        for (int i=0; i<col1.size(); ++i)
        {
            if (!col1[i]->getAlive())
            {
                if (col1[i]->getCreatureID() == "tiger" || col1[i]->getCreatureID() == "bulldog")
                {
                    col1.clear();
                    break;
                }
                else if (col1[i]->getCreatureID() == "Unicorn")
                {
                    col1.erase(col1.begin()+i);
                    positionUpdate();
                    break;
                }
                else
                {
                    col1[i]->setAlive(true);
                }
            }
        }
    }

    if (col2.size() > 0)
    {
        for (int i=0; i<col2.size(); ++i)
        {
            if (!col2[i]->getAlive())
            {
                if (col2[i]->getCreatureID() == "tiger" || col2[i]->getCreatureID() == "bulldog")
                {
                    col2.clear();
                    break;
                }
                else if (col2[i]->getCreatureID() == "Unicorn")
                {
                    col2.erase(col2.begin()+i);
                    positionUpdate();
                    break;
                }
                else
                {
                    col2[i]->setAlive(true);
                }
            }
        }
    }
    
    if (col1.size() == 0 && col2.size() == 0)
    {
        return false;
    }

    return true;
}

void TargetBank::positionUpdate()
{
    for(int i=0; i<col1.size(); ++i)
    {
        col1[i]->setYPos(900 - 144 * i);
    }

    for(int i=0; i<col2.size(); ++i)
    {
        col2[i]->setYPos(900 - 144 * i);
    }
}

Creature* TargetBank::getColCreature(int column, int index)
{
    if(column == 0)
    {
        return col1[index];
    }
    else
    {
        return col2[index];
    }
}