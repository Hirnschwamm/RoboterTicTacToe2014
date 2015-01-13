#include "TicTacToeAction.h"
#include <TTTIdle.h>


TicTacToeAction::TicTacToeAction(bool robotStarts, std::vector<std::vector<WayPoint> >* waypoints, ArPathPlanningTask* pt, ArMap* myMap) :
    ArAction("TicTacToeAction", "A game of Tic Tac Toe")
{
    state = NULL;
    this->startPose = ArPose(0, 0, 0);
    this->robotStarts = robotStarts;
    this->waypoints = waypoints;
    this->pathPlanningTask = pt;
    this->myMap = myMap;
    this->pt = new PathTask(myRobot, pt, myMap, ArPose(0, 0, 0), this);
}

TicTacToeAction::~TicTacToeAction(){
    delete pt;
    acts.closePort();
    ArAction::deactivate();
    delete state;
}

void TicTacToeAction::activate(){
    //printf("TicTacToe: Activate. State: IDLE\n");

    //acts.openPort(myRobot);

    ArAction::activate();

    if(!returnState){
        returnState = new TTTIdle(myRobot, this, robotStarts);
    }

    state = returnState;

    myRobot->addUserTask("PathTask", 0, pt);
}

void TicTacToeAction::deactivate(){
    ArAction::deactivate();
}

ArActionDesired* TicTacToeAction::fire(ArActionDesired currentDesired){
    myDesired.reset();
    if(state && pt->isIdle()){
        state->fire(&myDesired);
    }else{
        printf("No State, or Pathtask is active!\n");
    }

    return &myDesired;
}

TicTacToeState* TicTacToeAction::getState(){
    return state;
}

void TicTacToeAction::setState(TicTacToeState* newState){
    if(state){
        delete state;
    }

    this->state = newState;
}

ArACTS_1_2* TicTacToeAction::getActs(){
    return &acts;
}

TTTField* TicTacToeAction::getField(){
    return &field;
}

ArPose TicTacToeAction::getStartPose(){
    return startPose;
}

std::vector<std::vector<WayPoint> >* TicTacToeAction::getWaypoints(){
    return waypoints;
}

void TicTacToeAction::printBlobInfo(ArACTSBlob &blob){

    ArLog::log(ArLog::Normal, " Area: %d",blob.getArea());
    ArLog::log(ArLog::Normal, " BoundingBox: (%d, %d, %d, %d)",
    blob.getTop(), blob.getLeft(), blob.getBottom(), blob.getRight());
    ArLog::log(ArLog::Normal, " Position: (%d, %d)",
    blob.getXCG(), blob.getYCG());
}

void TicTacToeAction::goTo(ArPose goal, TicTacToeState* returnState){
    if(pt){
        delete pt;
    }

    pt = new PathTask(myRobot, pathPlanningTask, myMap, goal, this);
    printf("LOLOLOLOLO\n");
    pt->setReturnState(returnState);
    printf("LOLOLOLOLO2\n");
    pt->setIdle(false);
    printf("LOLOLOLOLO3\n");
    myRobot->addUserTask("PathTask", 0, pt);
    printf("LOLOLOLOLO4\n");
}

