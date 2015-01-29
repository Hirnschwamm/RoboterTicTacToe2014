#include "TTTObserving.h"
#include <TTTFetching.h>

#define PI 3.1415

TTTObserving::TTTObserving() : TicTacToeState(NULL, NULL), turnTo(NULL, NULL)
{
}

TTTObserving::TTTObserving(ArRobot *myRobot, TicTacToeAction *action, int numberOfCurrentPlayerPieces) :
    TicTacToeState(myRobot, action),
    turnTo(myRobot, action->getActs()){
    state = ALIGNING;
    this->numberOfCurrentPlayerPieces = numberOfCurrentPlayerPieces;
    timer = 0;

    point north = {382, 197};
    points.push_back(north);
    point west = {150, 226};
    points.push_back(west);
    point south = {299, 297};
    points.push_back(south);
    point east = {575, 241};
    points.push_back(east);

    ArPTZ* ptz = myRobot->getPTZ();
    ptz->tilt(-15.0);

    myRobot->setHeading(150.0);
}

TTTObserving::~TTTObserving(){

}

void TTTObserving::fire(ArActionDesired *currentDesired){
    int newNumberOfPlayerPieces = action->getActs()->getNumBlobs(PLAYERPIECESCHANNEL);

    ArACTSBlob piece;
    bool b = action->getActs()->getBlob(1, 1, &piece);

    return;

    switch(state){
    case ALIGNING:

        printf("%f\n", myRobot->getPose().getTh());

       if(myRobot->getTh() < 145){
            myRobot->setHeading(150);
        }else{
            myRobot->setRotVel(0.0);
            state = OBSERVING;
        }
        break;
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
        bool b;

        for(int i = 0; i < newNumberOfPlayerPieces; i++){
            b = action->getActs()->getBlob(PLAYERPIECESCHANNEL, newNumberOfPlayerPieces, &piece);
        }

        if(b){
            printf("b = true\n");
        }else{
            printf("b = false\n");
        }

        if(b){
            int margin = 40;
            if(std::abs(piece.getXCG() - newPiecePos[0]) < margin &&
                std::abs(piece.getYCG() - newPiecePos[1]) < margin   ){
                timer++;
            }else{
                timer = 0;
            }

            if(timer > CONFIRMATIONTIME){
                state = CONFIRMATION;
            }

            //printf("XCG: %d, newPiecePos: %d\n", piece.getXCG(), newPiecePos[0]);
            //printf("%d\n", action->getActs()->getNumBlobs(PLAYERPIECESCHANNEL));
            //printf("%d\n", b);

            newPiecePos[0] = piece.getXCG();
            newPiecePos[1] = piece.getYCG();
        }
        printf("WAITING: %d\n", timer);
    }   break;
    case CONFIRMATION:{
        float shortestDistance = 100000.0f;
        point blobPos = {piece.getXCG(), piece.getYCG()};
        int closestPointIndex = -1;
        int currentDistancePoint;
        int currentDistanceLine;
        bool closestFeatureIsLine = false;

        for(int i = 0; i < points.size(); i++){
            currentDistancePoint = distanceTo(points[i], blobPos);
            currentDistanceLine = distanceTo(points[i], points[(i+1) % points.size()], blobPos);
            if(currentDistancePoint < shortestDistance || currentDistanceLine < shortestDistance){
                closestPointIndex = i;
                if(currentDistancePoint < currentDistanceLine){
                    shortestDistance = currentDistancePoint;
                }else{
                    shortestDistance = currentDistanceLine;
                    closestFeatureIsLine = true;
                }
            }
        }

        if(!closestFeatureIsLine){
            switch(closestPointIndex){
            case(0):
                action->getField()->field[0][0] = action->getField()->turn() % 2;
            break;
            case(1):
                action->getField()->field[0][2] = action->getField()->turn() % 2;
            break;
            case(2):
                action->getField()->field[2][2] = action->getField()->turn() % 2;
            break;
            case(3):
                action->getField()->field[2][0] = action->getField()->turn() % 2;
            break;
            }
        }else{
            switch(closestPointIndex){
            case(0):
                action->getField()->field[0][1] = action->getField()->turn() % 2;
            break;
            case(1):
                action->getField()->field[1][2] = action->getField()->turn() % 2;
            break;
            case(2):
                action->getField()->field[2][1] = action->getField()->turn() % 2;
            break;
            case(3):
                action->getField()->field[1][0] = action->getField()->turn() % 2;
            break;
            }
        }
    }
    }

}

float TTTObserving::distanceTo(point a, point b){
    float d1 = (a.x - b.x) * (a.x - b.x);
    float d2 = (a.y - b.y) * (a.y - b.y);

    return sqrt(d1 + d2);
}

float TTTObserving::distanceTo(point l1, point l2, point a){
    float lineSquaredX = (l1.x - l2.x) * (l1.x - l2.x);
    float lineSquaredY = (l1.y - l2.y) * (l1.y - l2.y);
    float exp1 = (l2.y - l1.y)*a.x - (l2.x - l1.x)*a.y + l2.x*l1.y - l2.y*l1.x;
    float exp2 = (sqrt(lineSquaredY + lineSquaredX));
    return (float)std::abs((int)exp1) / exp2;
}



void TTTObserving::getCellFromCoordinates(int x, int y, int *cellX, int *cellY){
    WayPoint wp;
    PathUtil::findNextWpAll(x, y, &wp, action->getWaypoints());

    *cellX = wp.x;
    *cellY = wp.y;
}

void TTTObserving::printBlobInfo(ArACTSBlob &blob){

    ArLog::log(ArLog::Normal, " Area: %d",blob.getArea());
    ArLog::log(ArLog::Normal, " BoundingBox: (%d, %d, %d, %d)",
    blob.getTop(), blob.getLeft(), blob.getBottom(), blob.getRight());
    ArLog::log(ArLog::Normal, " Position: (%d, %d)",
    blob.getXCG(), blob.getYCG());

}
