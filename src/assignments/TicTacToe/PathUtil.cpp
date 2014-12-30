#include "PathUtil.h"
#include <iostream>

PathUtil::PathUtil()
{

}

void PathUtil::init(ArMap *map, std::vector<WayPoint*> *all1d) {
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!AOSIDJHOAISDHJOIADHO\n\n\n");
    ArLog::log(ArLog::Normal, "Goals: %i", map->findMapObjectsOfType("goal").size());

    std::list<ArMapObject*> mapPoints = map->findMapObjectsOfType("goal");
    std::list<ArMapObject*>::const_iterator iterator;

    int distToField = 200;
    std::vector<std::vector<WayPoint> > tmpWayPoints;

    //init TTT field
    for (int x = 0; x < 3; x++) {
        std::vector<WayPoint> newVec;
        tmpWayPoints.push_back(newVec);
        for (int y = 0; y < 3; y++) {
            WayPoint emptyWP(0, 0, -1);
            emptyWP.blocked = true;
            tmpWayPoints[x].push_back(emptyWP);
        }
    }

    for (iterator = mapPoints.begin(); iterator != mapPoints.end(); iterator++) {
        ArMapObject *curObj = *iterator;
        //printf("Name: %i, %i, %i, %i\n", sizeof(curObj->getName()[0]), (int) sizeof(*(curObj->getName())), (int) (sizeof(*(curObj->getName())) / sizeof(curObj->getName()[0])), (int) ((sizeof(*(curObj->getName())) / sizeof(curObj->getName()[0])) > 1));
        //is a TTT field, 1 char, '0' - '8'
        if ((sizeof(*(curObj->getName())) / sizeof(curObj->getName()[0])) > 1 || curObj->getName()[0] < '0' || curObj->getName()[0] > '8') continue;
        WayPoint *tmpWP = new WayPoint(curObj->getPose().getX(), curObj->getPose().getY(), (int) curObj->getName()[0] - '0');
        tmpWP->blocked = true;
        int xPos = tmpWP->id % 3;
        int yPos = (int) floor(tmpWP->id / 3);
        if (xPos != 1 || yPos != 1) tmpWP->blocked = false;

        if (xPos == 0) tmpWP->y += distToField;
        if (xPos == 2) tmpWP->y -= distToField;
        if (yPos == 0) tmpWP->x -= distToField;
        if (yPos == 2) tmpWP->x += distToField;

        tmpWayPoints[xPos][yPos] = *tmpWP;
        printf("Goal %i: %ix%i\n", (int) curObj->getName()[0] - '0', (int) curObj->getPose().getX(), (int) curObj->getPose().getY());
    }

    //create edges
    for (int x = 0; x < (int) tmpWayPoints.size(); x++) {
        for (int y = 0; y < (int) tmpWayPoints[x].size(); y++) {
            if (x + 1 < (int) tmpWayPoints.size()       && !tmpWayPoints[x + 1][y].blocked)      tmpWayPoints[x][y].wayPoints.push_back(&tmpWayPoints[x + 1][y]);
            if (x - 1 > -1                              && !tmpWayPoints[x - 1][y].blocked)                             tmpWayPoints[x][y].wayPoints.push_back(&tmpWayPoints[x - 1][y]);
            if (y + 1 < (int) tmpWayPoints[x].size()    && !tmpWayPoints[x][y + 1].blocked)   tmpWayPoints[x][y].wayPoints.push_back(&tmpWayPoints[x][y + 1]);
            if (y - 1 > -1                              && !tmpWayPoints[x][y - 1].blocked)                             tmpWayPoints[x][y].wayPoints.push_back(&tmpWayPoints[x][y - 1]);
            //ArLog::log(ArLog::Normal, "%i: %ix%i", wayPoints[grid.X][grid.Y].id, grid.X, grid.Y);
            //wayPoints[grid.X][grid.Y].listConnections();
        }
    }

    //std::vector<WayPoint*> all1d;
    int index = 0;
    for (int x = 0; x < (int) tmpWayPoints.size(); x++) {
        //std::vector<WayPoint*> tmpVec;
        //wayPoints->push_back(&tmpVec);
        for (int y = 0; y < (int) tmpWayPoints[x].size(); y++) {
            //all1d->push_back(&tmpWayPoints[x][y]);
            all1d->at(index)->x = tmpWayPoints[x][y].x;
            all1d->at(index)->y = tmpWayPoints[x][y].y;
            all1d->at(index)->id = tmpWayPoints[x][y].id;
            all1d->at(index)->blocked = tmpWayPoints[x][y].blocked;
            index++;
            //tmpVec.push_back(&tmpWayPoints[x][y]);
            //printf("Cur: %i, %i, %i\n", x, y, tmpWayPoints[x][y].id);
            //ArLog::log(ArLog::Normal, "%i: %ix%i", (*(*wayPoints)[x])[y]->id, x, y);
            //(*(*wayPoints)[x])[y]->listConnections();
        }
    }

    //for(int i = 0; i < all1d->size(); i++) printf("%i/%i: %ix%i\n", i, all1d->at(i)->id, all1d->at(i)->x, all1d->at(i)->y);

    /*
    std::vector<WayPoint*> path;
    std::vector<WayPoint*> best;
    path.push_back(&tmpWayPoints[0][0]);
    bool foundPath = findPath(&tmpWayPoints[0][0], &tmpWayPoints[2][2], &path, &best);
    printf("Path found (%i): %i\n", (int) foundPath, (int) best.size());
    for (int i = 0; i < best.size(); i++) printf("%i wp: %i\n", i, best[i]->id);
    */
}

bool PathUtil::findPath(WayPoint *start, WayPoint *end, std::vector<WayPoint*> *path, std::vector<WayPoint*> *best) {
    //ArLog::log(ArLog::Normal, "Call: %i", depth);
    WayPoint *curWp = (*path)[path->size() - 1];
    if (curWp == end) {
        //ArLog::log(ArLog::Normal, "---Call: %i >? %i", (int) best->size(), (int) path->size());
        if (best->size() == 0 || path->size() < best->size()) {
            //ArLog::log(ArLog::Normal, "---Call: %i", path->size());
            best->clear();
            for (int i = 0; i < path->size(); i++) best->push_back(((*path)[i]));
            //printf(">Path: %i\n", best->size());
            //for (int i = 0; i < best->size(); i++) printf(">> %i: %ix%i\n", (*best)[i]->id, (*best)[i]->x, (*best)[i]->y);
            return true;
        }
    }
    if (best->size() > 0 && path->size() >= best->size()) return false;
    bool foundPath = false;
    for (int i = 0; i < curWp->wayPoints.size(); i++) {
        //Already visited
        bool visited = false;
        for (int j = 0; j < (int) path->size(); j++) if (((*path)[j]) == (curWp->wayPoints[i])) visited = true;
        if (!visited) {
            std::vector<WayPoint*> tmpPath;
            for (int k = 0; k < (int) path->size(); k++) tmpPath.push_back((*path)[k]);
            tmpPath.push_back(curWp->wayPoints[i]);
            if (findPath(start, end, &tmpPath, best)) {

                foundPath = true;
            }
        }
    }

    return foundPath;
}

void PathUtil::findNextWp(int x, int y, WayPoint *wp, std::vector<std::vector<WayPoint> > *wayPoints) {
    WayPoint tmpWp(x, y, -1);

    WayPoint grid(0, 0, 0);
    wp->x = 0;
    wp->y = 0;
    for (grid.x = 0; grid.x < (int) (*wayPoints).size(); grid.x++) {
        //printf("WP search: %i\n", (*wayPoints)[grid.x].size());
        for (grid.y = 0; grid.y < (int) (*wayPoints)[grid.x].size(); grid.y++) {
            //printf("WP search: %i\n", grid.y);
            //ArLog::log(ArLog::Normal, "%i: %ix%i", (*wayPoints)[grid.x][grid.y].id, grid.x, grid.y);
            if (!(*wayPoints)[grid.x][grid.y].blocked && (*wayPoints)[grid.x][grid.y].distance(tmpWp) < (*wayPoints)[wp->x][wp->y].distance(tmpWp)) {
                wp->x = grid.x;
                wp->y = grid.y;
            }
            //wayPoints[grid.X][grid.Y].listConnections();
        }
    }
}

void PathUtil::findNextWpAll(int x, int y, WayPoint *wp, std::vector<std::vector<WayPoint> > *wayPoints) {
    WayPoint tmpWp(x, y, -1);

    WayPoint grid(0, 0, 0);
    wp->x = 0;
    wp->y = 0;
    for (grid.x = 0; grid.x < (int) (*wayPoints).size(); grid.x++) {
        //printf("WP search: %i\n", (*wayPoints)[grid.x].size());
        for (grid.y = 0; grid.y < (int) (*wayPoints)[grid.x].size(); grid.y++) {
            //printf("WP search: %i\n", grid.y);
            //ArLog::log(ArLog::Normal, "%i: %ix%i", (*wayPoints)[grid.x][grid.y].id, grid.x, grid.y);
            if ((*wayPoints)[grid.x][grid.y].distance(tmpWp) < (*wayPoints)[wp->x][wp->y].distance(tmpWp)) {
                wp->x = grid.x;
                wp->y = grid.y;
            }
            //wayPoints[grid.X][grid.Y].listConnections();
        }
    }
}

int PathUtil::findNextWp(int x, int y, std::vector<WayPoint*> *allWps) {
    WayPoint tmpWp(x, y, -1);
    int best = 0;

    for (int i = 0; i < allWps->size(); i++) {
        if (!(*allWps)[i]->blocked && (*allWps)[i]->distance(tmpWp) < (*allWps)[best]->distance(tmpWp)) best = i;
    }

    return best;
}
