#include "TTTObserving.h"

TTTObserving::TTTObserving() : TicTacToeState(NULL, NULL)
{
}

TTTObserving::TTTObserving(ArRobot *myRobot, TicTacToeAction *action) :
    TicTacToeState(myRobot, action){

}

TTTObserving::~TTTObserving(){

}

void TTTObserving::fire(ArActionDesired *currentDesired){

}
