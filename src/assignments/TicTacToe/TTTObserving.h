#ifndef TTTOBSERVING_H
#define TTTOBSERVING_H

#include <TicTacToeState.h>
#include <ArACTS.h>
#include <TurnTo.h>
#include <math.h>

#define CONFIRMATIONTIME 30
#define FOCALLENGTH 822
#define PLAYERPIECEWIDTH 11

struct point{
    int x;
    int y;

};

enum TTTOBSERVINGSTATE{PREALIGN, ALIGNING, OBSERVING, WAITINGFORCONFIRMATION, CONFIRMATION, TEMP};

class TTTObserving : public TicTacToeState
{
public:
    TTTObserving();
    TTTObserving(ArRobot* myRobot, TicTacToeAction* action, int numberOfCurrentPlayerPieces);
    void printBlobInfo(ArACTSBlob &blob);

    ~TTTObserving();

    void fire(ArActionDesired* currentDesired);

private:
    int numberOfCurrentPlayerPieces;
    int newPiecePos[2];
    int timer;
    TTTOBSERVINGSTATE state;

    std::vector<point> points;

    float distanceTo(point a, point b);
    float distanceTo(point l1, point l2, point a);
    bool inRectangle(point a, point b, point c, point d, point p);
    double triangleArea(point a, point b, point c);
    double rectangleArea(point a, point b, point c, point d);
    bool intersect(point p, point lineStart, point lineEnd, point *intersection);
    void getCellFromCoordinates(int x, int y, int* cellX, int* cellY);

    std::vector<std::vector<point> > xCoords;
    std::vector<std::vector<point> > yCoords;
    bool inPolygon(std::vector<point> polygon, point p);
    double polygonArea(std::vector<point> polygon);
    bool getBlobFieldByScreenCoords(point blobPos, point* blobFieldPos);
};

#endif // TTTOBSERVING_H
