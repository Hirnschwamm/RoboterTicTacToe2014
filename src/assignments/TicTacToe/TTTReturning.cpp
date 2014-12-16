#include "TTTReturning.h"

TTTReturning::TTTReturning() : TicTacToeState(NULL, NULL)
{
}

TTTReturning::TTTReturning(ArRobot *myRobot, TicTacToeAction *action):
    TicTacToeState(myRobot, action){

}

TTTReturning::~TTTReturning(){

}

void TTTReturning::fire(ArActionDesired *currentDesired){

}
