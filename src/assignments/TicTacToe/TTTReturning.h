#ifndef TTTRETURNING_H
#define TTTRETURNING_H

#include <TicTacToeState.h>
#include <TTTObserving.h>
#include <GoTo.h>
#include <PathUtil.h>

//TODO: Ímplement Returning!
class TTTReturning : public TicTacToeState
{
public:
    TTTReturning();
    TTTReturning(ArRobot* myRobot, TicTacToeAction* action, WayPoint *firstWP);

    ~TTTReturning();

    void fire(ArActionDesired* currentDesired);

private:
    GoTo* goTo;
    std::vector<WayPoint*> path;
    WayPoint* startWayPointOnGraph;
    WayPoint startWayPoint;
};

#endif // TTTRETURNING_H
