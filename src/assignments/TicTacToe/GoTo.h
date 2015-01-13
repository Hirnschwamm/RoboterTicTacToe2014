#ifndef GOTO_H
#define GOTO_H

#include <Aria.h>
#include <TicTacToeAction.h>
#include <TicTacToeState.h>
#include "waypoint.h"
#include <math.h>

class GoTo
{
public:
    GoTo(std::vector<WayPoint*>* path, ArRobot *robot, TicTacToeAction* action, TicTacToeState* callingState, bool targetAngle = false);
    virtual bool fire(ArActionDesired *myDesired);

protected:
    ArActionDesired myDesired; // what the action wants to do
    ArPose target;
    std::vector<WayPoint*>* path;
    bool targetAngle;
    bool initDirection;
    int state;
    int stateTime;
    int wpPos;
    ArRobot *myRobot;
    void stateChange(int change);

    TicTacToeAction* action;
    TicTacToeState* callingState;

};

#endif
