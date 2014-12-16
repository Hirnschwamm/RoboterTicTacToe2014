#ifndef TTTPLACING_H
#define TTTPLACING_H

#include <TicTacToeState.h>


//TODO: Implement Placing!
class TTTPlacing : public TicTacToeState
{
public:
    TTTPlacing();
    TTTPlacing(ArRobot* myRobot, TicTacToeAction* action);

    ~TTTPlacing();

    void fire(ArActionDesired* currentDesired);

private:


};

#endif // TTTPLACING_H
