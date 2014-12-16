#ifndef TTTFETCHING_H
#define TTTFETCHING_H

#include <TicTacToeState.h>
#include <FindAndLift.h>

#define ROBOTPIECESCHANNEL 1

enum TTTFETCHINGSTATE{TURNING, FETCHING};

class TTTFetching : public TicTacToeState
{
public:
    TTTFetching();
    TTTFetching(ArRobot* myRobot, TicTacToeAction* action);

    ~TTTFetching();

    void fire(ArActionDesired* currentDesired);

private:
    FindAndLift findAndLift;

    ArPTZ* ptz;

    TTTFETCHINGSTATE state;

};

#endif // TTTFETCHING_H
