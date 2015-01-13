#include "GoTo.h"

GoTo::GoTo(std::vector<WayPoint*>* path, ArRobot *robot, TicTacToeAction *action, bool targetAngle) {
    this->path = path;
    this->targetAngle= targetAngle;
    this->state = 0;
    this->stateTime = 0;
    this->initDirection = true;
    this->wpPos = 0;
    this->myRobot = robot;
    this->action = action;
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


    switch(state) {
        case 0: { //initial angle adjustment
            myRobot->setVel(0);
            int turnDir = 1;

            int turnSpeed = (targetHeading - curPos.getTh());

            if ((int)(myRobot->getTh() - targetHeading + 360) % 360>180) {
                turnDir = 1;
            } else {
                turnDir = -1;
            }
            if (turnSpeed < 0) turnSpeed *= -1;
            if (turnSpeed < 1) turnSpeed = 0;
            if (turnSpeed > 5) turnSpeed = 5;

            //myRobot->setRotVel(turnSpeed * turnDir);
            myRobot->setHeading(targetHeading);

            int deltaHeading = ((int)(curPos.getTh() - targetHeading) + 360) % 360;
            if (deltaHeading > 180) deltaHeading = 360 - deltaHeading;
            if (deltaHeading < 2) stateChange(1);
            if (stateTime > 30) stateChange(2);
            break;
        }

        case 1: { //check angle (unecessary / old code)
            if (curPos.getTh() < targetHeading -1 || curPos.getTh() > targetHeading + 1) {
                stateChange(-1);
            } else {
                stateChange(1);
                initDirection = false;
            }
            break;
        }

        case 2: { //move to point
            int deltaHeading = ((int)(curPos.getTh() - targetHeading) + 360) % 360;
            if (deltaHeading > 180) deltaHeading = 360 - deltaHeading;
            if (deltaHeading > 10) {
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
                if (turnSpeed > 5) turnSpeed = 5;

                //myRobot->setRotVel(turnSpeed * turnDir);
                myRobot->setHeading(targetHeading);
                //myRobot->setDeltaHeading(turnDir * deltaHeading);

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

        case 3: { //if waypoints have angle, rotate to it
            if (targetAngle) {
                myRobot->setHeading((double) target.getTh());
                 if(curPos.getTh() > target.getTh() - 2 && curPos.getTh() < target.getTh() + 2) stateChange(1);
            } else {
                stateChange(2);
            }
            break;
        }

        case 4: { //check angle (unecessary / old code)
            if(curPos.getTh() < target.getTh() - 2 || curPos.getTh() > target.getTh() + 2) {
                stateChange(-1);
            } else {
                stateChange(1);
            }
            break;
        }

        case 5: { //done / next waypoint
            if (wpPos > path->size() - 2) {
                stateChange(1);
                ArLog::log(ArLog::Normal, "Done.");
                return true;
            } else {
                ArLog::log(ArLog::Normal, "reached %i/%i (%i) %ix%i", wpPos, path->size(), curWp->id, curWp->x, curWp->y);
                wpPos++;
                if (wpPos == 1 || wpPos == path->size() - 1) {
                    //next wp
                    stateChange(-5);
                } else {
                    //readjust own position
                    stateChange(1);
                }
            }
            break;
        }

        case 6: { //adjust own position by laser readings
            ArLaser *myLaser = action->getLaser();
            //system("clear");

            myLaser->lockDevice();
            if (myLaser->isTryingToConnect()) {
                printf("Laser trying to connect");
            } else if (myLaser->isConnected()) {
                printf("Has Laser %i, %i, %i\n", myRobot->hasLaser(myLaser), myLaser->isTryingToConnect(), myLaser->isConnected());
                std::vector<ArSensorReading> *myReadings = myLaser->getRawReadingsAsVector();
                for (int i = 0; i < myReadings->size(); i++) {
                    if (i % 5 > 0) continue;
                    ArSensorReading curReading = (*myReadings)[i];
                    if (i < 10) printf(" ");
                    if (i < 100) printf(" ");
                    //printf("%i reading: %i\n", i, (int)curReading.getRange());
                }

                if (myReadings->size() > 180) {
                    int rotvel = (*myReadings)[95].getRange() - (*myReadings)[85].getRange();
                    if (rotvel < -10) rotvel = -10;
                    if (rotvel > 10) rotvel = 10;
                    if (rotvel * rotvel > 25) {
                        myRobot->setRotVel(rotvel/2);
                    } else {
                        ArPose rePose(0, 0, 0);

                        ArPose upRight = action->getMap()->getLineMaxPose();
                        ArPose lowLeft = action->getMap()->getLineMinPose();

                        myRobot->setRotVel(0);
                        int angle = round(myRobot->getPose().getTh() / 90) * 90;
                        rePose.setTh(angle);
                        switch (angle) {
                        case 0: {
                            printf("0>");
                            rePose.setY((int)(*myReadings)[180].getRange() + lowLeft.getY());
                            rePose.setX(-(int)(*myReadings)[90].getRange() + upRight.getX());
                            break;
                        }

                        case 90: {
                            printf("90>");
                            rePose.setY(-(int)(*myReadings)[90].getRange() + upRight.getY());
                            rePose.setX(-(int)(*myReadings)[180].getRange() + upRight.getX());
                            break;
                        }

                        case -180:
                        case 180: {
                            printf("180>");
                            rePose.setY(-(int)(*myReadings)[180].getRange() + upRight.getY());
                            rePose.setX((int)(*myReadings)[90].getRange() + lowLeft.getX());
                            break;
                        }

                        case -90: {
                            printf("-90>");
                            rePose.setY((int)(*myReadings)[90].getRange() + lowLeft.getY());
                            rePose.setX((int)(*myReadings)[180].getRange() + lowLeft.getX());
                            break;
                        }

                        }
                        printf("My Pose: %ix%i / %i; %i\n", (int)rePose.getX(), (int)rePose.getY(), (int)rePose.getTh(), angle);
                        myRobot->moveTo(rePose);
                        stateChange(-6);
                    }

                }

            } else {
                myLaser->asyncConnect();
            }

            myLaser->unlockDevice();
            break;
        }
    }
    stateTime++;

    return false;
}

void GoTo::stateChange(int change) {
    state += change;
    //ArLog::log(ArLog::Normal, "Statechange: %i -> %i; after %i ticks", state - change, state, stateTime);
    stateTime = 0;
}
