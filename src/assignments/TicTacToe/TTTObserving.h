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

enum TTTOBSERVINGSTATE{ALIGNING, OBSERVING, WAITINGFORCONFIRMATION, CONFIRMATION, TEMP};

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
    TurnTo turnTo;
    TTTOBSERVINGSTATE state;

    std::vector<point> points;

    float distanceTo(point a, point b);
    float distanceTo(point l1, point l2, point a);
    void getCellFromCoordinates(int x, int y, int* cellX, int* cellY);
};

#endif // TTTOBSERVING_H
