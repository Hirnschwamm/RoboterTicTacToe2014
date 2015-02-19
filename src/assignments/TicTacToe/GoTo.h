#ifndef GOTO_H
#define GOTO_H

#include <Aria.h>
#include <waypoint.h>
#include <math.h>
#include <ArLaser.h>
#include <TicTacToeAction.h>

class GoTo
{
public:
    GoTo(std::vector<WayPoint*>* path, ArRobot *robot, TicTacToeAction *action, bool targetAngle = false);
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
    int accuracy;
    ArRobot *myRobot;
    TicTacToeAction *action;
    void stateChange(int change);
};

#endif
