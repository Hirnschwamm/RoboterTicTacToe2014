#include "TTTIdle.h"

TTTIdle::TTTIdle(ArRobot* myRobot, TicTacToeAction* action, bool robotStarts) : TicTacToeState(myRobot, action){
    this->robotStarts = robotStarts;
}

TTTIdle::~TTTIdle(){
}

void TTTIdle::fire(ArActionDesired* currentDesired){
    if(robotStarts){
        printf("STATETRANSITION: IDLE--->FETCHING\n");
        action->setState(new TTTFetching(myRobot, action));
    }else{
        printf("STATETRANSITION: IDLE--->OBSERVING\n");
    }
}
