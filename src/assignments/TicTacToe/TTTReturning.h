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
    TTTReturning(ArRobot* myRobot, TicTacToeAction* action);

    ~TTTReturning();

    void fire(ArActionDesired* currentDesired);

private:
    GoTo* goTo;
    std::vector<WayPoint*> path;
};

#endif // TTTRETURNING_H
