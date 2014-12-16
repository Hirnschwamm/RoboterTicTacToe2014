#ifndef PATHUTIL_H
#define PATHUTIL_H

#include "waypoint.h"
#include "Aria.h"

class PathUtil
{
public:
    PathUtil();
    //static std::vector<std::vector<WayPoint> >* wayPoints;
    static void init(ArMap* map, std::vector<WayPoint *> *all1d);
    static bool findPath(WayPoint *start, WayPoint *end, std::vector<WayPoint*> *path, std::vector<WayPoint *> *bestPath);
    static void findNextWp(int x, int y, WayPoint *wp, std::vector<std::vector<WayPoint> > *wayPoints);
    static int findNextWp(int x, int y, std::vector<WayPoint *> *allWps);

private:
    static int distToField;
};

#endif // STATE_H
