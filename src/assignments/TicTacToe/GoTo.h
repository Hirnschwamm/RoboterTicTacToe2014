#include <Aria.h>
#include "waypoint.h"

class GoTo
{
public:
    GoTo(std::vector<WayPoint*>* path, bool targetAngle = false);
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
};
