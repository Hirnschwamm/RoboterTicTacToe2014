#include "TTTReturning.h"

TTTReturning::TTTReturning() :
    TicTacToeState(NULL, NULL)
{
}

TTTReturning::TTTReturning(ArRobot *myRobot, TicTacToeAction *action):
    TicTacToeState(myRobot, action),
     startWayPoint(action->getStartPose().getX(), action->getStartPose().getY(), action->getStartPose().getTh())
{

    WayPoint robotWayPoint(myRobot->getPose().getX(), myRobot->getPose().getY(), myRobot->getPose().getTh());

    WayPoint startWayPointOnGraphIndex(0, 0, 0);
    PathUtil::findNextWp(startWayPoint.x, startWayPoint.y, &startWayPointOnGraphIndex, action->getWaypoints());
    WayPoint robotWayPointOnGraphIndex(0, 0, 0);
    PathUtil::findNextWp(robotWayPoint.x, robotWayPoint.y, &robotWayPointOnGraphIndex, action->getWaypoints());

    startWayPointOnGraph = &action->getWaypoints()->at(startWayPointOnGraphIndex.x).at(startWayPointOnGraphIndex.y);
    WayPoint* robotWayPointOnGraph = &action->getWaypoints()->at(robotWayPointOnGraphIndex.x).at(robotWayPointOnGraphIndex.y);

    std::vector<WayPoint*> startPath;
    startPath.push_back(startWayPointOnGraph);
    PathUtil::findPath(robotWayPointOnGraph, startWayPointOnGraph, &startPath, &path);

    path.push_back(&startWayPoint);

    goTo = new GoTo(&path, myRobot, true);
}

TTTReturning::~TTTReturning(){
    if(goTo){
        delete goTo;
    }
}

void TTTReturning::fire(ArActionDesired *currentDesired){

    if(goTo->fire(currentDesired)){
        printf("STATETRANSITION: RETURNING--->OBSERVING\n");
       action->setState(new TTTObserving(myRobot, action));
    }
}
