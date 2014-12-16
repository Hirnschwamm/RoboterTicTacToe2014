#include "waypoint.h"
#include <math.h>
#include "ArLog.h"

WayPoint::WayPoint(int x, int y, int id) :
    x(x),
    y(y),
    id(id)
{
}

bool WayPoint::nearby(WayPoint other, int dist) {
    if (distance(other) > dist) return false;
    return true;
}

double WayPoint::distance(WayPoint other) {
    int distX = x - other.x;
    int distY = y - other.y;
    return sqrt((double)((distX * distX) + (distY * distY)));
}

void WayPoint::listConnections() {
    std::vector<WayPoint*>::iterator wpIt;
    ArLog::log(ArLog::Normal, "Tracing %i", id);
    for (wpIt = this->wayPoints.begin(); wpIt != this->wayPoints.end(); ++wpIt) {
        WayPoint *tmpWp = (*wpIt);
        ArLog::log(ArLog::Normal, "    > %i", tmpWp->id);
    }
}

ArPose WayPoint::getPose() {
    ArPose pose(x, y);
    return pose;
}
