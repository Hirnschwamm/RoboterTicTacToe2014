#include "TTTIdlestate.h"

TTTIdleState::TTTIdleState(ArRobot* myRobot, TicTacToeAction* action) : TicTacToeState(myRobot, action){
}

TTTIdleState::~TTTIdleState(){
}

void TTTIdleState::fire(ArActionDesired* currentDesired){
    printf("IDLE\n");
}
