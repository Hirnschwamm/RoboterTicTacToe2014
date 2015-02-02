#include "TTTObserving.h"
#include <TTTFetching.h>

#define PI 3.1415

TTTObserving::TTTObserving(): TicTacToeState(NULL, NULL)
{
}

TTTObserving::TTTObserving(ArRobot *myRobot, TicTacToeAction *action, int numberOfCurrentPlayerPieces) :
    TicTacToeState(myRobot, action){
    state = PREALIGN;
    this->numberOfCurrentPlayerPieces = numberOfCurrentPlayerPieces;
    timer = 0;
    /*
    point north = {382, 197};
    points.push_back(north);
    point west = {150, 226};
    points.push_back(west);
    point south = {299, 297};
    points.push_back(south);
    point east = {575, 241};
    points.push_back(east);
    */

    //initialize points
    point p0 = {0, 0};
    points.push_back(p0);
    point p1 = {0, 120};
    points.push_back(p1);
    point p2 = {0, 179};
    points.push_back(p2);
    point p3 = {0, 247};
    points.push_back(p3);
    point p4 = {0, 347};
    points.push_back(p4);
    point p5 = {0, 478};
    points.push_back(p5);
    point p6 = {705, 0};
    points.push_back(p6);
    point p7 = {705, 153};
    points.push_back(p7);
    point p8 = {705, 211};
    points.push_back(p8);
    point p9 = {705, 284};
    points.push_back(p9);
    point p10 = {705, 478};
    points.push_back(p10);

    //initialize polygons
    //x
    std::vector<point> x0;
    x0.push_back(points[2]);
    x0.push_back(points[5]);
    x0.push_back(points[10]);
    xCoords.push_back(x0);

    std::vector<point> x1;
    x1.push_back(points[1]);
    x1.push_back(points[2]);
    x1.push_back(points[10]);
    x1.push_back(points[9]);
    xCoords.push_back(x1);

    std::vector<point> x2;
    x2.push_back(points[1]);
    x2.push_back(points[9]);
    x2.push_back(points[6]);
    x2.push_back(points[0]);
    xCoords.push_back(x2);

    //y
    std::vector<point> y0;
    y0.push_back(points[0]);
    y0.push_back(points[3]);
    y0.push_back(points[7]);
    y0.push_back(points[6]);
    yCoords.push_back(y0);

    std::vector<point> y1;
    y1.push_back(points[3]);
    y1.push_back(points[4]);
    y1.push_back(points[8]);
    y1.push_back(points[7]);
    yCoords.push_back(y1);

    std::vector<point> y2;
    y2.push_back(points[4]);
    y2.push_back(points[5]);
    y2.push_back(points[10]);
    y2.push_back(points[8]);
    yCoords.push_back(y2);


    ArPTZ* ptz = myRobot->getPTZ();
    ptz->tilt(-15.0);

    //myRobot->setHeading(150.0);
}

TTTObserving::~TTTObserving(){

}

void TTTObserving::fire(ArActionDesired *currentDesired){
    int newNumberOfPlayerPieces = action->getActs()->getNumBlobs(PLAYERPIECESCHANNEL);

    ArACTSBlob piece;
    bool b = action->getActs()->getBlob(1, 1, &piece);

    switch(state){
    case PREALIGN: {
        printf("#");

        if (myRobot->getPose().getTh() < -5 || myRobot->getPose().getTh() > 5) {
            myRobot->setHeading(0);
            return;
        }

        ArLaser *myLaser = action->getLaser();
        myLaser->lockDevice();
        if (myLaser->isTryingToConnect()) {
            printf("Laser trying to connect");
        } else if (myLaser->isConnected()) {
            std::vector<ArSensorReading> *myReadings = myLaser->getRawReadingsAsVector();
            if (myReadings->size() > 180) {
                int rotvel = (*myReadings)[95].getRange() - (*myReadings)[85].getRange();
                if (rotvel < -10) rotvel = -10;
                if (rotvel > 10) rotvel = 10;
                if (rotvel * rotvel > 25) {
                    myRobot->setRotVel(rotvel/2);
                } else {
                    myRobot->setRotVel(0);
                    int angle = round(myRobot->getPose().getTh() / 90) * 90;
                    ArPose newAngle(myRobot->getPose().getX(), myRobot->getPose().getY(), angle);
                    myRobot->moveTo(newAngle);
                    state = ALIGNING;
                }
            }
        }
        myLaser->unlockDevice();
        break;
    }

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
        ArACTSBlob tempBlob;
        point blobFieldPos;
        for(int i = 1; i <= action->getActs()->getNumBlobs(PLAYERPIECESCHANNEL); i++){
            action->getActs()->getBlob(PLAYERPIECESCHANNEL, i, &tempBlob);
            point blobPos = {tempBlob.getXCG(), tempBlob.getYCG()};
            getBlobFieldByScreenCoords(blobPos, &blobFieldPos);
            if(action->getField()->field[blobFieldPos.x][blobFieldPos.y] < 0){
                break;
            }

        }

        if (blobFieldPos.x > -1) {
            action->getField()->field[blobFieldPos.x][blobFieldPos.y] = action->getField()->turn() % 2;
            printf("Blob field: %ix%i\n", blobFieldPos.x, blobFieldPos.y);
            //action->setState(new TTTFetching(myRobot, action));
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

bool TTTObserving::inRectangle(point a, point b, point c, point d, point p) {
    double sumTriangles = triangleArea(a, p, d) +
                 triangleArea(d, p, c) +
                 triangleArea(c, p, b) +
                 triangleArea(p, b, a);
    if (sumTriangles > rectangleArea(a, b, c, d)) return false;
    return true;
}

bool TTTObserving::getBlobFieldByScreenCoords(point blobPos, point* blobFieldPos){
    blobFieldPos->x = blobFieldPos->y = -1;
    for (int i = 0; i < 3; i++) {
        if (inPolygon(xCoords[i], blobPos)) {
            blobFieldPos->x = i;
            break;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (inPolygon(yCoords[i], blobPos)) {
            blobFieldPos->y = i;
            break;
        }
    }
    int tmpX = blobFieldPos->x;
    blobFieldPos->x = blobFieldPos->y;
    blobFieldPos->y = 2 - tmpX;

    if(blobFieldPos->x == -1 || blobFieldPos->y == -1){
        return false;
    }else{
        return true;
    }
}

double TTTObserving::triangleArea(point a, point b, point c) {
    return std::abs((((a.x - c.x) * (b.y - a.y)) - ((a.x - b.x) * (c.y - a.y)))/2);
}

double TTTObserving::rectangleArea(point a, point b, point c, point d) {
    return std::abs(((a.x * b.y) - (b.x * a.y)) +
            ((b.x * c.y) - (c.x * b.y)) +
            ((c.x * d.y) - (d.x * c.y)) +
            ((d.x * a.y) - (a.x * d.y))
            )/2;
}

bool TTTObserving::inPolygon(std::vector<point> polygon, point p) {
      int i, j, c = 0;
      for (i = 0, j = polygon.size()-1; i < polygon.size(); j = i++) {
        if (((polygon[i].y > p.y) != (polygon[j].y > p.y)) &&
            (p.x < (polygon[j].x - polygon[i].x) * (p.y-polygon[i].y) / (polygon[j].y-polygon[i].y) + polygon[i].x))
           c = !c;
      }
      return c;
}

double TTTObserving::polygonArea(std::vector<point> polygon) {
    int area = 0;
    int poly = polygon.size();
    for (int i = 0; i < poly; i++) area += (polygon[i].x * polygon[(i + 1) % poly].y);
    for (int i = 0; i < poly; i++) area -= (polygon[(i + 1) % poly].x * polygon[i].y);
    return std::abs(area) / 2;
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

bool TTTObserving::intersect(point p, point lineStart, point lineEnd, point *intersection) {
    return ((p.x < lineStart.x && p.x > lineEnd.x) || (p.x > lineStart.x && p.x < lineEnd.x) &&
            (p.y < lineStart.y && p.y > lineEnd.x) || (p.y > lineStart.y && p.y > lineEnd.x));
}

