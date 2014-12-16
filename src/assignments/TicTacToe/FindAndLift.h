#ifndef ACTSACTION_H
#define ACTSACTION_H

#include<ArRobot.h>
#include<ArACTS.h>
#include<ArGripper.h>
#include<ArSonyPTZ.h>

#define SCREENWIDTH 715
#define SCREENHEIGHT 120

#define focalLength 822

enum FINDANDLIFTSTATE{IDLE, SEARCHING, ADJUSTING, APPROACHING, LIFTING, DONE};


class FindAndLift
{
public:
    FindAndLift(ArRobot* myRobot, ArACTS_1_2* acts);
    ~FindAndLift();

    bool fire(ArActionDesired* currentDesired);

    virtual void activate();
    virtual void deactivate();

    void printChannel(int channel);
    void printBlobInfo(ArACTSBlob &blob);

protected:
    ArRobot* myRobot;
    ArACTS_1_2* acts;
    ArACTSBlob blob;
    ArGripper* gripper;
    ArPTZ* ptz;

    FINDANDLIFTSTATE state;

    float getDistance(float objectWidth){
        return (focalLength * objectWidth) / objectWidth;
    }

};

#endif // ACTSACTION_H
