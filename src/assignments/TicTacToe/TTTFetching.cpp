#include "TTTFetching.h"
#include "TTTIdle.h"
#include <TTTReturning.h>

TTTFetching::TTTFetching() :
    TicTacToeState(NULL, NULL),
    findAndLift(NULL, NULL, NULL)
{
}

TTTFetching::TTTFetching(ArRobot *myRobot, TicTacToeAction *action) :
    TicTacToeState(myRobot, action),
    findAndLift(myRobot, action->getActs(), action){

    ptz = myRobot->getPTZ();
    ptz->tilt(-12.0);

    state = TURNING;

}

TTTFetching::~TTTFetching(){

}

void TTTFetching::fire(ArActionDesired* currentDesired){
    //TEMP//
    //state = FETCHING;
    //TEMP//
    switch(state){
    case(TURNING):{
        //myRobot->setRotVel(-5.0f);
        myRobot->setHeading(93.0);
        if(myRobot->getTh() > 90.0 && myRobot->getTh() < 95.0){
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
