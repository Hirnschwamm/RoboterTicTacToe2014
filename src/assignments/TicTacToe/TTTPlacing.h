#ifndef TTTPLACING_H
#define TTTPLACING_H

#include <TicTacToeState.h>
#include <PathUtil.h>
#include <GoTo.h>


//TODO: Implement Placing!
class TTTPlacing : public TicTacToeState
{
public:
    TTTPlacing();
    TTTPlacing(ArRobot* myRobot, TicTacToeAction* action);

    ~TTTPlacing();

    void fire(ArActionDesired* currentDesired);

private:
    int targetX;
    int targetY;
    int myState;
    GoTo *myGoto;
    std::vector<WayPoint*> finalPath;
    ArGripper *gripper;
};

#endif // TTTPLACING_H
