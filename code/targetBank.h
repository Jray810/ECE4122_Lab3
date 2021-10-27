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
 *      26OCT2021 ED-019: Added refresh() function
 **/

#ifndef TARGETBANK_H
#define TARGETBANK_H

#include <vector>
#include "unicorn.h"
#include "woodland.h"
#include "evil.h"

class TargetBank
{
public:
    TargetBank();
    ~TargetBank();

    void targetReset();
    bool refresh();
    void positionUpdate();

    // Setters

    // Getters
    int getCol1Size(){return col1.size();}
    int getCol2Size(){return col2.size();}
    Creature* getColCreature(int column, int index);

private:
    std::vector<Creature*> col1;
    std::vector<Creature*> col2;
    std::vector<Creature*> woodlanders;
    std::vector<Creature*> evildoers;
};

#endif