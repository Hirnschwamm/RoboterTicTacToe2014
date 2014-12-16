#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <vector>
#include <ArRobot.h>

class WayPoint
{
public:
    WayPoint(int x, int y, int id);
    bool nearby(WayPoint other, int dist);
    double distance(WayPoint other);
    ArPose getPose();
    void listConnections();
    int x;
    int y;
    int id;
    bool blocked;
    std::vector<WayPoint*> wayPoints;
};

#endif // WAYPOINT_H
