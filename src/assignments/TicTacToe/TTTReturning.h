#ifndef TTTRETURNING_H
#define TTTRETURNING_H

#include <TicTacToeState.h>

//TODO: Ímplement Returning!
class TTTReturning : public TicTacToeState
{
public:
    TTTReturning();
    TTTReturning(ArRobot* myRobot, TicTacToeAction* action);

    ~TTTReturning();

    void fire(ArActionDesired* currentDesired);

private:

};

#endif // TTTRETURNING_H
