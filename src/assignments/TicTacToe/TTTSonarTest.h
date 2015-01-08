#ifndef TTTSONARTEST_H
#define TTTSONARTEST_H

#include <TicTacToeState.h>
#include <ArLaser.h>

class TTTSonarTest : public TicTacToeState
{
public:
    TTTSonarTest();
    TTTSonarTest(ArRobot* myRobot, TicTacToeAction* action);

    ~TTTSonarTest();

    void fire(ArActionDesired* currentDesired);

    ArLaser *myLaser;
    bool turn;
};

#endif // TTTSONARTEST_H
