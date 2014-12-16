#include "TTTGameOver.h"

TTTGameOver::TTTGameOver() : TicTacToeAction(NULL, NULL)
{
}

TTTGameOver::TTTGameOver(ArRobot *myRobot, TicTacToeAction *action) :
    TicTacToeAction(myRobot, action){

}

TTTGameOver::~TTTGameOver(){

}

void TTTGameOver::fire(ArActionDesired *currentDesired){

}
