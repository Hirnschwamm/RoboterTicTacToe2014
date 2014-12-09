#ifndef TICTACTOESTATE_H
#define TICTACTOESTATE_H

#include<TicTacToeAction.h>
#include<ArRobot.h>

class TicTacToeAction;

class TicTacToeState{
public:
    TicTacToeState(ArRobot* myRobot, TicTacToeAction* action){
        this->myRobot = myRobot;
        this->action = action;
    }

    virtual void fire(ArActionDesired* currentDesired) = 0;

protected:
    ArRobot* myRobot;
    TicTacToeAction* action;


};

#endif // TICTACTOESTATE_H
