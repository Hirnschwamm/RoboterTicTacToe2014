#include "TTTIdle.h"
#include <TTTFetching.h>
#include <TTTSonarTest.h>

bool TTTIdle::robotReady = false;

TTTIdle::TTTIdle(ArRobot* myRobot, TicTacToeAction* action) : TicTacToeState(myRobot, action){

    handler = Aria::getKeyHandler();
    if(handler == NULL){
         handler = new ArKeyHandler;
         Aria::setKeyHandler(handler);
         myRobot->attachKeyHandler(handler);
    }

    ArGlobalFunctor setReadyCallbackFunctor(&setReadyCallback);
    handler->addKeyHandler('r', &setReadyCallbackFunctor);

    system("clear");
    printf("Please localize robot. Press  r for (r)eady to start.\n");

    WayPoint startPos(0, 0, 0);

    path.push_back(&startPos);
    path.push_back(&startPos);

    goTo = new GoTo(&path, myRobot, action, false);
}

TTTIdle::~TTTIdle(){
    delete handler;
}

void TTTIdle::fire(ArActionDesired* currentDesired){
    if(robotReady){
        if(goTo->fire(currentDesired)){
            if(action->getRobotStarts()){
                printf("STATETRANSITION: IDLE--->FETCHING\n");
                action->setState(new TTTFetching(myRobot, action));
            }else{
                printf("STATETRANSITION: IDLE--->OBSERVING\n");
                action->setState(new TTTObserving(myRobot, action));
            }
        }
    }
}

void TTTIdle::setReadyCallback(){
    robotReady = true;
}
