#ifndef TTTIDLESTATE_H
#define TTTIDLESTATE_H

#include<TicTacToeState.h>
#include<TTTFetching.h>

class TTTIdle : public TicTacToeState
{
public:
    TTTIdle(ArRobot* myRobot, TicTacToeAction* action, bool robotStarts);
    ~TTTIdle();

    void fire(ArActionDesired* currentDesired);

private:
    bool robotStarts;
};

#endif // TTTIDLESTATE_H
