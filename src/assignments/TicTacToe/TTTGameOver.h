#ifndef TTTGAMEOVER_H
#define TTTGAMEOVER_H

#include <TicTacToeState.h>

enum GAMEOVERSTATE{ROBOTWIN, DRAW, PLAYERWIN};

class TTTGameOver : public TicTacToeState
{
public:
    TTTGameOver();
    TTTGameOver(ArRobot *myRobot, TicTacToeAction *action, GAMEOVERSTATE gameResult);

    ~TTTGameOver();

    void fire(ArActionDesired* currentDesired);

private:


};

#endif // TTTGAMEOVER_H
