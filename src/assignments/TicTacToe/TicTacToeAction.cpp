#include "TicTacToeAction.h"
#include <TTTIdlestate.h>


TicTacToeAction::TicTacToeAction() : ArAction("TicTacToeAction", "A game of Tic Tac Toe")
{
    state = NULL;
}

TicTacToeAction::~TicTacToeAction(){
   delete state;
}

void TicTacToeAction::activate(){
    setState(new TTTIdleState(this->myRobot, this));
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
