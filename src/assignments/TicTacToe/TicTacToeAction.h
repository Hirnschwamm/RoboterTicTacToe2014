#ifndef TICTACTOEACTION_H
#define TICTACTOEACTION_H

#include <ArAction.h>
#include <TicTacToeState.h>
#include <ArACTS.h>
#include <tttfield.h>
#include <waypoint.h>
#include <ArMap.h>
#include <ArLaser.h>

#define ROBOTPIECESCHANNEL 1
#define PLAYERPIECESCHANNEL 2

class TicTacToeState;

class TicTacToeAction : public ArAction
{
public:
    TicTacToeAction(bool robotStarts, std::vector<std::vector<WayPoint> >* waypoints, ArMap *map);
    ~TicTacToeAction();

    virtual void activate();
    virtual void deactivate();

    ArActionDesired* fire(ArActionDesired currentDesired);

    TicTacToeState* getState();
    void setState(TicTacToeState* newState);

    ArACTS_1_2* getActs();

    TTTField* getField();
    ArMap* getMap();
    ArLaser *getLaser();

    std::vector<std::vector<WayPoint> >* getWaypoints();

    ArPose getStartPose();

    void printBlobInfo(ArACTSBlob &blob);

private:
    bool robotStarts;

    ArPose startPose;

    TTTField field;
    ArMap *map;
    ArLaser *myLaser;

    std::vector<std::vector<WayPoint> >* waypoints;

    TicTacToeState* state;
    ArACTS_1_2 acts;

    ArActionDesired myDesired;
};

#endif // TICTACTOEACTION_H
