#include "TicTacToeAction.h"
#include <TTTIdle.h>


TicTacToeAction::TicTacToeAction(bool robotStarts) : ArAction("TicTacToeAction", "A game of Tic Tac Toe")
{
    state = NULL;
    this->robotStarts = robotStarts;
}

TicTacToeAction::~TicTacToeAction(){
    acts.closePort();
    ArAction::deactivate();
    delete state;
}

void TicTacToeAction::activate(){
    printf("TicTacToe: Activate. State: IDLE");

    acts.openPort(myRobot);

    setState(new TTTIdle(this->myRobot, this, robotStarts));
    ArAction::activate();
}

void TicTacToeAction::deactivate(){
    ArAction::deactivate();
}

ArActionDesired* TicTacToeAction::fire(ArActionDesired currentDesired){

    if(state){
        state->fire(&currentDesired);
    }else{
        printf("No State!\n");
    }
    return 0;
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

void TicTacToeAction::printBlobInfo(ArACTSBlob &blob){

    ArLog::log(ArLog::Normal, " Area: %d",blob.getArea());
    ArLog::log(ArLog::Normal, " BoundingBox: (%d, %d, %d, %d)",
    blob.getTop(), blob.getLeft(), blob.getBottom(), blob.getRight());
    ArLog::log(ArLog::Normal, " Position: (%d, %d)",
    blob.getXCG(), blob.getYCG());

}

