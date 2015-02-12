#include "TTTSonarTest.h"
#include <math.h>

TTTSonarTest::TTTSonarTest() : TicTacToeState(NULL, NULL)
{
}

TTTSonarTest::TTTSonarTest(ArRobot *myRobot, TicTacToeAction *action) : TicTacToeState(myRobot, action) {
    //class for testing only
    myLaser = myRobot->findLaser(1);
    turn = true;
}

TTTSonarTest::~TTTSonarTest()
{

}

void TTTSonarTest::fire(ArActionDesired *currentDesired) {
    if (!turn) return;

    system("clear");
    /*
    for (int i = 0; i < myRobot->getNumSonar(); i++) {
        if (i < 10) printf(" ");
        printf("%i Sonar: %i\n", i, myRobot->getSonarRange(i));
    }
    */



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
            printf("%i reading: %i\n", i, (int)curReading.getRange());
        }

        if (false && myReadings->size() > 180) {
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

                case 180: {
                    printf("180>");
                    rePose.setY(-(int)(*myReadings)[180].getRange() + upRight.getY());
                    rePose.setX((int)(*myReadings)[90].getRange() + lowLeft.getX());
                    break;
                }

                case 270: {
                    printf("270>");
                    rePose.setY((int)(*myReadings)[90].getRange() + lowLeft.getY());
                    rePose.setX((int)(*myReadings)[180].getRange() + lowLeft.getX());
                    break;
                }

                }
                printf("My Pose: %ix%i / %i; %i\n", (int)rePose.getX(), (int)rePose.getY(), (int)rePose.getTh(), angle);
                myRobot->moveTo(rePose);
            }

        }

    } else {
        myLaser->asyncConnect();
    }

    myLaser->unlockDevice();
}
