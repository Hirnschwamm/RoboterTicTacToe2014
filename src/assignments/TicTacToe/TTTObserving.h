#ifndef TTTOBSERVING_H
#define TTTOBSERVING_H

#include <TicTacToeState.h>
#include <ArACTS.h>
#include <TurnTo.h>
#include <math.h>

#define CONFIRMATIONTIME 70
#define FOCALLENGTH 703
#define PLAYERPIECEWIDTH 12

enum TTTOBSERVINGSTATE{ALIGNING, OBSERVING, WAITINGFORCONFIRMATION, CONFIRMATION, TEMP};

class TTTObserving : public TicTacToeState
{
public:
    TTTObserving();
    TTTObserving(ArRobot* myRobot, TicTacToeAction* action, int numberOfCurrentPlayerPieces);

    ~TTTObserving();

    void fire(ArActionDesired* currentDesired);

private:
    int numberOfCurrentPlayerPieces;
    int newPiecePos[2];
    int timer;
    TurnTo turnTo;
    TTTOBSERVINGSTATE state;

    int getDistanceTo(int w, int deltaX);
    void getCellFromCoordinates(int x, int y, int* cellX, int* cellY);
};

#endif // TTTOBSERVING_H
