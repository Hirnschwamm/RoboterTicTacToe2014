#ifndef TTTIDLESTATE_H
#define TTTIDLESTATE_H

#include<TicTacToeState.h>

class TTTIdleState : public TicTacToeState
{
public:
    TTTIdleState(ArRobot* myRobot, TicTacToeAction* action);
    ~TTTIdleState();

    void fire(ArActionDesired* currentDesired);
};

#endif // TTTIDLESTATE_H
