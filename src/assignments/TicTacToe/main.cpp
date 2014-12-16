#include <Aria.h>
#include <defaultrobotserver.h>

#include<TicTacToeAction.h>
#include<waypoint.h>
#include<PathUtil.h>
#include<GoTo.h>

int main(int argc, char **argv) {

    DefaultRobotServer server;
    server.init(argc, argv);

    ArMap* map = server.getMap();
    ArRobot *robot = server.getRobot();

    std::vector<WayPoint*> all1d;
    std::vector<std::vector<WayPoint> > wayPoints;
    //init TTT field
    for (int x = 0; x < 3; x++) {
        std::vector<WayPoint> newVec;
        wayPoints.push_back(newVec);
        for (int y = 0; y < 3; y++) {
            WayPoint emptyWP(0, 0, -1);
            emptyWP.blocked = true;
            wayPoints[x].push_back(emptyWP);
        }
    }

    for (int i = 0; i < 9; i++) all1d.push_back(new WayPoint(0, 0, 0));
    PathUtil::init(map, &all1d);
    printf("#########################\n");
    //for(int i = 0; i < all1d.size(); i++) printf("%i/%i: %ix%i\n", i, all1d.at(i)->id, all1d.at(i)->x, all1d.at(i)->y);

    for(int i = 0; i < all1d.size(); i++) {
        WayPoint *tmpWP = all1d.at(i);
        int xPos = tmpWP->id % 3;
        int yPos = (int) floor(tmpWP->id / 3);
        wayPoints[yPos][xPos] = *tmpWP;
    }

    for (int x = 0; x < (int) wayPoints.size(); x++) {
        for (int y = 0; y < (int) wayPoints[x].size(); y++) {
            if (x + 1 < (int) wayPoints.size()       && !wayPoints[x + 1][y].blocked)   wayPoints[x][y].wayPoints.push_back(&wayPoints[x + 1][y]);
            if (x - 1 > -1                           && !wayPoints[x - 1][y].blocked)   wayPoints[x][y].wayPoints.push_back(&wayPoints[x - 1][y]);
            if (y + 1 < (int) wayPoints[x].size()    && !wayPoints[x][y + 1].blocked)   wayPoints[x][y].wayPoints.push_back(&wayPoints[x][y + 1]);
            if (y - 1 > -1                           && !wayPoints[x][y - 1].blocked)   wayPoints[x][y].wayPoints.push_back(&wayPoints[x][y - 1]);
            //ArLog::log(ArLog::Normal, "%i (%i): %ix%i", wayPoints[x][y].id, wayPoints[x][y].blocked, wayPoints[x][y].x, wayPoints[x][y].y);
            //wayPoints[grid.X][grid.Y].listConnections();
        }
    }

    std::vector<WayPoint*> path;
    std::vector<WayPoint*> bestPath;

    std::vector<WayPoint*> finalPath;
    WayPoint myPos((int)robot->getPose().getX(), (int)robot->getPose().getY(), -1);
    WayPoint dest(-1750, -1600, -1);

    WayPoint first(-1, -1, -1);
    PathUtil::findNextWp(myPos.x, myPos.y, &first, &wayPoints);
    path.push_back(&wayPoints[first.x][first.y]);

    WayPoint last(-1, -1, -1);
    PathUtil::findNextWp(dest.x, dest.y, &last, &wayPoints);

    PathUtil::findPath(&wayPoints[first.x][first.y], &wayPoints[last.x][last.y], &path, &bestPath);

    finalPath.push_back(&myPos);
    for (int i = 0; i < bestPath.size(); i++) finalPath.push_back(bestPath[i]);
    finalPath.push_back(&dest);

    printf("Final, wps: %i\n", (int) finalPath.size());
    for (int i = 0; i < finalPath.size(); i++) printf("%i (%i): %ix%i\n", i, finalPath[i]->id, finalPath[i]->x, finalPath[i]->y);

    GoTo gotoObj(&finalPath, false);
    server.addAction(gotoObj, 49);
    gotoObj.activate();

    /*TicTacToeAction tictactoeaction(true);
    server.addAction(tictactoeaction);
    tictactoeaction.activate();*/

    ArLog::log(ArLog::Normal, "run...");
    server.run();

    Aria::exit(0);
    return 0;
}
