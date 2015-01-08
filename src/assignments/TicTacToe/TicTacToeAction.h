#ifndef TICTACTOEACTION_H
#define TICTACTOEACTION_H

#include <ArAction.h>
#include <TicTacToeState.h>
#include <ArACTS.h>
#include <tttfield.h>
#include <waypoint.h>
#include <Arnl.h>
#include <pathtask.h>

#define ROBOTPIECESCHANNEL 1
#define PLAYERPIECESCHANNEL 2

class TicTacToeState;
class PathTask;

class TicTacToeAction : public ArAction
{
public:
    TicTacToeAction(bool robotStarts, std::vector<std::vector<WayPoint> >* waypoints, ArPathPlanningTask* pt, ArMap* myMap);
    ~TicTacToeAction();

    virtual void activate();
    virtual void deactivate();

    ArActionDesired* fire(ArActionDesired currentDesired);

    TicTacToeState* getState();
    void setState(TicTacToeState* newState);

    ArACTS_1_2* getActs();

    TTTField* getField();

    std::vector<std::vector<WayPoint> >* getWaypoints();

    ArPose getStartPose();

    void printBlobInfo(ArACTSBlob &blob);

    void goTo(ArPose goal);

    void removePathTask(){
        myRobot->remUserTask("PathTask");
    }

private:
    bool robotStarts;

    ArPose startPose;

    ArMap* myMap;

    PathTask* pt;

    TTTField field;

    std::vector<std::vector<WayPoint> >* waypoints;

    TicTacToeState* state;
    ArACTS_1_2 acts;

    ArActionDesired myDesired;

    ArPathPlanningTask* pathPlanningTask;

};

#endif // TICTACTOEACTION_H
