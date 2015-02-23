#include "TTTIdle.h"
#include <TTTFetching.h>
#include <TTTSonarTest.h>

TTTIdle::TTTIdle(ArRobot* myRobot, TicTacToeAction* action) : TicTacToeState(myRobot, action){

}

TTTIdle::~TTTIdle(){
}

void TTTIdle::fire(ArActionDesired* currentDesired){

    if(action->getRobotStarts()){
        printf("STATETRANSITION: IDLE--->FETCHING\n");
        action->setState(new TTTFetching(myRobot, action));
    }else{
        printf("STATETRANSITION: IDLE--->OBSERVING\n");
        action->setState(new TTTObserving(myRobot, action));
    }
}
