#include "TTTIdle.h"
#include <TTTPlacing.h>

TTTIdle::TTTIdle(ArRobot* myRobot, TicTacToeAction* action, bool robotStarts) : TicTacToeState(myRobot, action){
    this->robotStarts = robotStarts;
    test = 0;
}

TTTIdle::~TTTIdle(){
}

void TTTIdle::fire(ArActionDesired* currentDesired){
    test++;
    if(test > 1000){
    action->setState(new TTTPlacing(myRobot, action));
    return;
    }else{
        return;
    }

    if(robotStarts){
        printf("STATETRANSITION: IDLE--->FETCHING\n");
        action->setState(new TTTPlacing(myRobot, action));
    }else{
        printf("STATETRANSITION: IDLE--->OBSERVING\n");
        action->setState(new TTTObserving(myRobot, action, 0));
    }
}
