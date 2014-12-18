#ifndef TTTGAMEOVER_H
#define TTTGAMEOVER_H

#include <TicTacToeState.h>

//TODO: Implement GameOver!
class TTTGameOver : public TicTacToeState
{
public:
    TTTGameOver();
    TTTGameOver(ArRobot *myRobot, TicTacToeAction *action);

    ~TTTGameOver();

    void fire(ArActionDesired* currentDesired);

private:


};

#endif // TTTGAMEOVER_H
