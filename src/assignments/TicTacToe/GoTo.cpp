#include "GoTo.h"

GoTo::GoTo(std::vector<WayPoint*>* path, ArRobot *robot, bool targetAngle) {
    this->path = path;
    this->targetAngle= targetAngle;
    this->state = 0;
    this->stateTime = 0;
    this->initDirection = true;
    this->wpPos = 0;
    this->myRobot = robot;
}

bool GoTo::fire(ArActionDesired *myDesired)
{
    int maxVel = 50;
    int minVel = 10;

    WayPoint* curWp = (*path)[wpPos];
    target = curWp->getPose();
    ArPose curPos = myRobot->getPose();

    double targetHeading = curPos.findAngleTo(target);
    //double targetHeading = atan2(curPos.getY() - target.getY(), curPos.getX() - target.getX()) * (180 / M_PI);
    double dist = curPos.findDistanceTo(target);

    //double targetHeading = acos((curPos.getY() - target.getY()) / dist)  * (180 / M_PI);

    ArLog::log(ArLog::Normal, "I'm at: %ix%i; %i / %i; %ix%i", (int) curPos.getX(), (int) curPos.getY(), (int) curPos.getTh(), (int) targetHeading, (int) target.getX(), (int) target.getY());


    //if (myRobot->isHeadingDone()) {
        switch(state) {
            case 0: {
                myRobot->setVel(0);
                //myDesired->setHeading(targetHeading);
                int turnDir = 1;
                //if (curPos.getTh() > targetHeading) turnDir = -1;

                int turnSpeed = (targetHeading - curPos.getTh());
                //if (turnSpeed < 0) {
                //    turnSpeed *= -1;
                //    turnDir = 1;
                //}
                if ((int)(myRobot->getTh() - targetHeading + 360) % 360>180) {
                    turnDir = 1;
                } else {
                    turnDir = -1;
                }
                if (turnSpeed < 0) turnSpeed *= -1;
                if (turnSpeed < 1) turnSpeed = 0;
                if (turnSpeed > 5) turnSpeed = 5;
                //if (turnSpeed < -5) turnSpeed = -5;
                //if (turnSpeed > 0 && turnSpeed < 3) turnSpeed = 3;
                //if (turnSpeed < 0 && turnSpeed > -3) turnSpeed = -3;

                myRobot->setRotVel(turnSpeed * turnDir);
                if (curPos.getTh() > targetHeading - 1 && curPos.getTh() < targetHeading + 1) stateChange(1);
                if (stateTime > 30) stateChange(2);
                break;
            }

            case 1: {
                if (curPos.getTh() < targetHeading -1 || curPos.getTh() > targetHeading + 1) {
                    stateChange(-1);
                } else {
                    stateChange(1);
                    initDirection = false;
                }
                break;
            }

            case 2: {
                if (curPos.getTh() < targetHeading - 10 || curPos.getTh() > targetHeading + 10) {
                    stateChange(-2);
                    //myRobot->setVel(0);
                } else {
                    int turnDir = 1;

                    int turnSpeed = (targetHeading - curPos.getTh());
                    if ((int)(myRobot->getTh() - targetHeading + 360) % 360>180) {
                        turnDir = 1;
                    } else {
                        turnDir = -1;
                    }
                    if (turnSpeed < 0) turnSpeed *= -1;
                    if (turnSpeed < 2) turnSpeed = 0;

                    myDesired->setRotVel(turnSpeed * turnDir);

                    int targetVel = minVel;
                    if (dist > maxVel * 2) {
                        targetVel = maxVel;
                    } else if (dist > minVel * 2) {
                        targetVel = dist / 2;
                    } else if (dist < 100) {
                        targetVel = 0;
                        stateChange(1);
                    }
                    myRobot->setVel(targetVel);
                }
                break;
            }

            case 3: {
                if (targetAngle) {
                    myRobot->setHeading((double) target.getTh());
                     if(curPos.getTh() > target.getTh() - 2 && curPos.getTh() < target.getTh() + 2) stateChange(1);
                } else {
                    stateChange(2);
                }
                break;
            }

            case 4: {
                if(curPos.getTh() < target.getTh() - 2 || curPos.getTh() > target.getTh() + 2) {
                    stateChange(-1);
                } else {
                    stateChange(1);
                }
                break;
            }

            case 5: {
                if (wpPos > path->size() - 1) {
                    stateChange(1);
                    ArLog::log(ArLog::Normal, "Done.");
                    return true;
                } else {
                    ArLog::log(ArLog::Normal, "reached %i/%i (%i) %ix%i", wpPos, path->size(), curWp->id, curWp->x, curWp->y);
                    wpPos++;
                    stateChange(-5);
                }
                break;
            }

            case 6: {

                break;
            }
        }
        stateTime++;
    //}

    /*
    if (myRobot->isHeadingDone()) {
        if (curPos.getTh() < targetHeading - 1 || curPos.getTh() > targetHeading + 1) {
            myDesired->setHeading(targetHeading);
        } else if (dist > 10) {
            state = 1;
            int targetVel = minVel;
            if (dist > maxVel * 2) {
                targetVel = maxVel;
            } else if (dist > minVel) {
                targetVel = dist;
            }
            myDesired->setVel(targetVel);
        } else if(targetAngle && (curPos.getTh() < target.getTh() - 2 || curPos.getTh() > target.getTh() + 2)) {
            state = 2;
            myDesired->setHeading((double) target.getTh());
        }

        if (dist < 10) {
            if (path->size() > wpPos + 1) {
                wpPos++;
            } else {
                myDesired->setVel(0);
                printf("Done.");
            }
        }

    }
    */


    return false;
}

void GoTo::stateChange(int change) {
    state += change;
    ArLog::log(ArLog::Normal, "Statechange: %i -> %i; after %i ticks", state - change, state, stateTime);
    stateTime = 0;
}
