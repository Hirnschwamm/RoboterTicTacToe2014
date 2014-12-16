#ifndef TTTOBSERVING_H
#define TTTOBSERVING_H

#include <TicTacToeState.h>

//TODO: Implement Observerving!
class TTTObserving : public TicTacToeState
{
public:
    TTTObserving();
    TTTObserving(ArRobot* myRobot, TicTacToeAction* action);

    ~TTTObserving();

    void fire(ArActionDesired* currentDesired);

private:

};

#endif // TTTOBSERVING_H
