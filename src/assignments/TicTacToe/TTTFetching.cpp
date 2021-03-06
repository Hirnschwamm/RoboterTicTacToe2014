#include "TTTFetching.h"
#include "TTTIdle.h"
#include <TTTReturning.h>

TTTFetching::TTTFetching() :
    TicTacToeState(NULL, NULL),
    findAndLift(NULL, NULL)
{
}

TTTFetching::TTTFetching(ArRobot *myRobot, TicTacToeAction *action) :
    TicTacToeState(myRobot, action),
    findAndLift(myRobot, action->getActs()){

    ptz = myRobot->getPTZ();
    ptz->tilt(-12.0);

    state = TURNING;

}

TTTFetching::~TTTFetching(){

}

void TTTFetching::fire(ArActionDesired* currentDesired){
    switch(state){
    case(TURNING):{
        myRobot->setRotVel(-2.5f);
        if(myRobot->getTh() < 85.0){
            state = FETCHING;
        }
    }break;
    case(FETCHING):
        if(this->findAndLift.fire(currentDesired)){
            printf("STATETRANSITION: FETCHING--->PLACING\n");
            this->action->setState(new TTTPlacing(myRobot, action));
            //this->action->setState(new TTTReturning(myRobot, action));
        };
        break;
    }
}
