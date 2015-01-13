#include "TTTIdle.h"
#include <TTTPlacing.h>
#include <TTTSonarTest.h>

TTTIdle::TTTIdle(ArRobot* myRobot, TicTacToeAction* action, bool robotStarts) : TicTacToeState(myRobot, action){
    this->robotStarts = robotStarts;
    test = 0;
}

TTTIdle::~TTTIdle(){
}

void TTTIdle::fire(ArActionDesired* currentDesired){

    action->setState(new TTTPlacing(myRobot, action));
    return;
    if(robotStarts){    
        printf("STATETRANSITION: IDLE--->FETCHING\n");
        action->setState(new TTTPlacing(myRobot, action));
    }else{
        printf("STATETRANSITION: IDLE--->OBSERVING\n");
        action->setState(new TTTObserving(myRobot, action, 0));
    }
}
