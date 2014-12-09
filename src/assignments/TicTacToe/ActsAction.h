#ifndef ACTSACTION_H
#define ACTSACTION_H

#include<ArAction.h>
#include<ArACTS.h>
#include<ArGripper.h>
#include<ArSonyPTZ.h>

#define SCREENWIDTH 715
#define SCREENHEIGHT 120

#define focalLength 822

enum STATE{IDLE, SEARCHING, ADJUSTING, APPROACHING, LIFTING, DONE};


class ActsAction : public ArAction
{
public:
    ActsAction();
    ~ActsAction();

    ArActionDesired *fire(ArActionDesired currentDesired);

    virtual void activate();
    virtual void deactivate();

    void printChannel(int channel);
    void printBlobInfo(ArACTSBlob &blob);

protected:
    ArACTS_1_2 acts;
    ArACTSBlob blob;
    ArGripper* gripper;
    ArPTZ* ptz;

    STATE state;

    float getDistance(float objectWidth){
        return (focalLength * objectWidth) / objectWidth;
    }

};

#endif // ACTSACTION_H
