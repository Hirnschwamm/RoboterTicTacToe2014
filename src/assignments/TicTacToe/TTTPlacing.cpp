#include "TTTPlacing.h"

TTTPlacing::TTTPlacing() : TicTacToeState(NULL, NULL)
{
}

TTTPlacing::TTTPlacing(ArRobot* myRobot, TicTacToeAction* action) :
    TicTacToeState(myRobot, action){

}

void TTTPlacing::fire(ArActionDesired *currentDesired){

}
