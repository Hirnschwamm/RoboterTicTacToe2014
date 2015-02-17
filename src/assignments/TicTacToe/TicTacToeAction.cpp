#include "TicTacToeAction.h"
#include <TTTIdle.h>


TicTacToeAction::TicTacToeAction(std::vector<std::vector<WayPoint> >* waypoints, ArMap *map, char* startingPlayer, char* difficulty) : ArAction("TicTacToeAction", "A game of Tic Tac Toe")
{
    state = NULL;
    this->startPose = ArPose(0, 0, 0);
    this->robotStarts = robotStarts;
    this->waypoints = waypoints;
    this->map = map;
    this->robotStarts = std::string("r").compare(startingPlayer) == 0;
    this->difficulty = atoi(difficulty) + 1;

    printf("diff: %d\n", this->difficulty);
}

TicTacToeAction::~TicTacToeAction(){
    acts.closePort();
    ArAction::deactivate();
    delete state;
}

void TicTacToeAction::activate(){
    printf("TicTacToe: Activate. State: IDLE");

    acts.openPort(myRobot);
    myLaser = myRobot->findLaser(1);
    myLaser->asyncConnect();

    setState(new TTTIdle(this->myRobot, this, robotStarts));
    ArAction::activate();
}

void TicTacToeAction::deactivate(){
    ArAction::deactivate();
}

ArActionDesired* TicTacToeAction::fire(ArActionDesired currentDesired){
    myDesired.reset();
    if(state){
        state->fire(&myDesired);
    }else{
        printf("No State!\n");
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

ArMap *TicTacToeAction::getMap()
{
    return map;
}

ArLaser *TicTacToeAction::getLaser()
{
    return myLaser;
}

ArPose TicTacToeAction::getStartPose(){
    return startPose;
}

bool TicTacToeAction::getRobotStarts(){
    return robotStarts;
}

int TicTacToeAction::getDifficulty(){
    return difficulty;
}

std::vector<std::vector<WayPoint> >* TicTacToeAction::getWaypoints(){
    return waypoints;
}

void TicTacToeAction::printBlobInfo(ArACTSBlob &blob){

    ArLog::log(ArLog::Normal, " Area: %d",blob.getArea());
    ArLog::log(ArLog::Normal, " BoundingBox: (%d, %d, %d, %d)", blob.getTop(), blob.getLeft(), blob.getBottom(), blob.getRight());
    ArLog::log(ArLog::Normal, " Position: (%d, %d)", blob.getXCG(), blob.getYCG());
}

