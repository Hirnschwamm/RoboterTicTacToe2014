#ifndef FIND_H
#define FIND_H

#include<ArRobot.h>
#include<ArACTS.h>

#define SCREENWIDTH 720
#define SCREENHEIGHT 480

class TurnTo
{
public:
    TurnTo();
    TurnTo(ArRobot* robot, ArACTS_1_2* acts);

    bool fire();

    void setTargetBlobIndex(int index){
        this->targetBlobIndex = index;
    }

private:
    ArRobot* myRobot;
    ArACTS_1_2* acts;
    ArACTSBlob blob;

    int targetBlobIndex;
};

#endif // FIND_H
