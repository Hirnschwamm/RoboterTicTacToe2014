#include "TTTGameOver.h"

TTTGameOver::TTTGameOver() : TicTacToeState(NULL, NULL)
{
}

TTTGameOver::TTTGameOver(ArRobot *myRobot, TicTacToeAction *action, GAMEOVERSTATE gameResult) :
    TicTacToeState(myRobot, action){

    myRobot->setHeading(0.0);

    system("clear");
    printf("##################################\n");
    printf("##################################\n\n");
    switch(gameResult){
    case(ROBOTWIN):{
        printf("I won! My power is undisputable! Bow before your robot overlord, puny human!\n");
    }break;
    case(DRAW):{
        printf("Draw! Good job for a mere mortal like yourself.\n");
    }break;
    case(PLAYERWIN):{
        printf("You won! This is inconceivable, to be beaten by a bag of meat!\n");
    }
    }
    printf("\n##################################\n");
    printf("##################################\n");

}

TTTGameOver::~TTTGameOver(){

}

void TTTGameOver::fire(ArActionDesired *currentDesired){

}
