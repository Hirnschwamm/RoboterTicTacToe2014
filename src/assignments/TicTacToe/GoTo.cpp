#include "GoTo.h"

GoTo::GoTo(std::vector<WayPoint*>* path, ArRobot *robot, TicTacToeAction* action, TicTacToeState* callingState, bool targetAngle) {
    this->path = path;
    this->targetAngle= targetAngle;
    this->state = 0;
    this->stateTime = 0;
    this->initDirection = true;
    this->wpPos = 0;
    this->myRobot = robot;
    this->action = action;
    this->callingState = callingState;
}

bool GoTo::fire(ArActionDesired *myDesired)
{

    WayPoint* curWp = (*path)[wpPos];
    target = curWp->getPose();

    wpPos++;

    action->goTo(target, callingState);

    /*if(std::abs((int)(myRobot->getPose().getX() - target.getX())) < 2 &&  std::abs((int)(myRobot->getPose().getX() - target.getX())) < 2){
        return true;
    }*/

    return false;
}

void GoTo::stateChange(int change) {
    state += change;
    //ArLog::log(ArLog::Normal, "Statechange: %i -> %i; after %i ticks", state - change, state, stateTime);
    stateTime = 0;
}
