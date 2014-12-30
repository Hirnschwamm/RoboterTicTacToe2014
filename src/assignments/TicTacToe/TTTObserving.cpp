#include "TTTObserving.h"
#include <TTTFetching.h>

#define PI 3.1415

TTTObserving::TTTObserving() : TicTacToeState(NULL, NULL), turnTo(NULL, NULL)
{
}

TTTObserving::TTTObserving(ArRobot *myRobot, TicTacToeAction *action, int numberOfCurrentPlayerPieces) :
    TicTacToeState(myRobot, action),
    turnTo(myRobot, action->getActs()){
    state = OBSERVING;
    this->numberOfCurrentPlayerPieces = numberOfCurrentPlayerPieces;
    timer = 0;
}

TTTObserving::~TTTObserving(){

}

void TTTObserving::fire(ArActionDesired *currentDesired){
    int newNumberOfPlayerPieces = action->getActs()->getNumBlobs(PLAYERPIECESCHANNEL);

    switch(state){
    case OBSERVING:
        if(newNumberOfPlayerPieces > numberOfCurrentPlayerPieces){
            ArACTSBlob piece;
            action->getActs()->getBlob(PLAYERPIECESCHANNEL, newNumberOfPlayerPieces, &piece);

            newPiecePos[0] = piece.getXCG();
            newPiecePos[1] = piece.getYCG();

            state = WAITINGFORCONFIRMATION;
        }
        break;
    case WAITINGFORCONFIRMATION:{
        ArACTSBlob piece;
        bool b = action->getActs()->getBlob(PLAYERPIECESCHANNEL, newNumberOfPlayerPieces, &piece);

        if(b){
        int margin = 30;
        if(std::abs(piece.getXCG() - newPiecePos[0]) < margin &&
           std::abs(piece.getYCG() - newPiecePos[1]) < margin   ){
            timer++;
        }else{
            timer = 0;
        }

        if(timer > CONFIRMATIONTIME){
            turnTo.setTargetBlobIndex(newNumberOfPlayerPieces);
            state = CONFIRMATION;
        }

        //printf("XCG: %d, newPiecePos: %d\n", piece.getXCG(), newPiecePos[0]);
        //printf("%d\n", action->getActs()->getNumBlobs(PLAYERPIECESCHANNEL));
        //printf("%d\n", b);

        newPiecePos[0] = piece.getXCG();
        newPiecePos[1] = piece.getYCG();
        }
        printf("WAITING: %d\n", timer);
    }
        break;
    case CONFIRMATION:
        if(turnTo.fire()){

            ArACTSBlob piece;
            action->getActs()->getBlob(PLAYERPIECESCHANNEL, newNumberOfPlayerPieces, &piece);

            int deltaX = piece.getRight() - piece.getLeft();
            int distance = getDistanceTo(PLAYERPIECEWIDTH, deltaX);

            int alpha = (myRobot->getTh() - 90.0) * PI / 180;
            int oppositeLeg = sin(alpha) * distance;
            int adjacentLeg = cos(alpha) * distance;

            int pieceXPos = myRobot->getPose().getX() + oppositeLeg;
            int pieceYPos = myRobot->getPose().getY() + adjacentLeg;

            int fieldXPos, fieldYPos;
            getCellFromCoordinates(pieceXPos, pieceYPos, &fieldXPos, &fieldYPos);

            action->getField()->field[fieldXPos][fieldYPos] = (action->getField()->turn() % 2);

            printf("STATETRANSITION: OBSERVING--->FETCHING\n");
            printf("X:%d Y:%d\n", fieldXPos, fieldYPos);
            action->setState(new TTTFetching(myRobot, action));
        }
        break;
    }

}

int TTTObserving::getDistanceTo(int w, int deltaX){
    return (FOCALLENGTH * w)/deltaX;
}

void TTTObserving::getCellFromCoordinates(int x, int y, int *cellX, int *cellY){
    WayPoint wp;
    PathUtil::findNextWpAll(x, y, &wp, action->getWaypoints());

    *cellX = wp.x;
    *cellY = wp.y;
}
