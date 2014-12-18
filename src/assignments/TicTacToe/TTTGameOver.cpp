#include "TTTGameOver.h"

TTTGameOver::TTTGameOver() : TicTacToeState(NULL, NULL)
{
}

TTTGameOver::TTTGameOver(ArRobot *myRobot, TicTacToeAction *action) :
    TicTacToeState(myRobot, action){

}

TTTGameOver::~TTTGameOver(){

}

void TTTGameOver::fire(ArActionDesired *currentDesired){

}
