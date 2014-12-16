#ifndef TICTACTOEACTION_H
#define TICTACTOEACTION_H

#include <ArAction.h>
#include <TicTacToeState.h>
#include <ArACTS.h>

class TicTacToeState;

class TicTacToeAction : public ArAction
{
public:
    TicTacToeAction(bool robotStarts);
    ~TicTacToeAction();

    virtual void activate();
    virtual void deactivate();

    ArActionDesired* fire(ArActionDesired currentDesired);

    TicTacToeState* getState();
    void setState(TicTacToeState* newState);

    ArACTS_1_2* getActs();

    void printBlobInfo(ArACTSBlob &blob);

private:
    TicTacToeState* state;
    bool robotStarts;
    ArACTS_1_2 acts;
};

#endif // TICTACTOEACTION_H
