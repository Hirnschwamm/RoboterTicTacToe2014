#include <Aria.h>
#include "waypoint.h"

class GoTo : public ArAction
{
public:
    GoTo(std::vector<WayPoint*>* path, bool targetAngle = false);
    virtual ArActionDesired *fire(ArActionDesired currentDesired);

protected:
    ArActionDesired myDesired; // what the action wants to do
    ArPose target;
    std::vector<WayPoint*>* path;
    bool targetAngle;
    bool initDirection;
    int state;
    int stateTime;
    int wpPos;
    void stateChange(int change);
};
