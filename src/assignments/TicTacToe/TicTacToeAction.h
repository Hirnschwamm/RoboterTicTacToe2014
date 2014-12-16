#ifndef TICTACTOEACTION_H
#define TICTACTOEACTION_H

#include <ArAction.h>
#include <TicTacToeState.h>

class TicTacToeState;

class TicTacToeAction : public ArAction
{
public:
    TicTacToeAction();
    ~TicTacToeAction();

    virtual void activate();
    virtual void deactivate();

    ArActionDesired* fire(ArActionDesired currentDesired);

    TicTacToeState* getState();
    void setState(TicTacToeState* newState);

private:
    TicTacToeState* state;

};

#endif // TICTACTOEACTION_H
