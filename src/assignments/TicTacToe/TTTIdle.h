#ifndef TTTIDLESTATE_H
#define TTTIDLESTATE_H

#include<TicTacToeState.h>
#include<TTTFetching.h>
#include<ArKeyHandler.h>

class TTTIdle : public TicTacToeState
{
public:
    TTTIdle(ArRobot* myRobot, TicTacToeAction* action);
    ~TTTIdle();

    void fire(ArActionDesired* currentDesired);

private:
    ArKeyHandler* handler;

    GoTo* goTo;
    std::vector<WayPoint*> path;

    static bool robotReady;
    static void setReadyCallback();
};

#endif TTTIDLESTATE_H
