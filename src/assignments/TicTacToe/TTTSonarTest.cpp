#include "TTTSonarTest.h"
#include <math.h>

TTTSonarTest::TTTSonarTest() : TicTacToeState(NULL, NULL)
{
}

TTTSonarTest::TTTSonarTest(ArRobot *myRobot, TicTacToeAction *action) : TicTacToeState(myRobot, action) {
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

        /*
        int minLeft = -1;
        int minRight = -1;

        int minLeftVal = 100000;
        int minRightVal = 100000;
        if (myReadings->size() > 10) {
            for (int i = 0; i < myReadings->size(); i++) {
                ArSensorReading curReading = (*myReadings)[i];
                if (i < 45) {
                    if (minLeft < 0 || curReading.getRange() < minLeftVal) {
                        minLeft = i;
                        minLeftVal = curReading.getRange();
                    }
                } else if (i > 135) {
                    if (minRight < 0 || curReading.getRange() < minRightVal) {
                       minRight = i;
                       minRightVal = curReading.getRange();
                   }
                }
            }
            if (minLeft > (180 - minRight)) {
                myRobot->setDeltaHeading(minLeft);
            } else {
                myRobot->setDeltaHeading(180 - minRight);
            }
            printf("Turning %i, %i, %i\n", minLeft, minRight, (int)myReadings->size());
            //turn = false;
        }
        */

        if (myReadings->size() > 170) {
            /*
            if ((*myReadings)[95].getRange() > (*myReadings)[85].getRange() + 10) {
                //turn left
                myRobot->setRotVel(5);
            } else if ((*myReadings)[85].getRange() > (*myReadings)[95].getRange() + 10) {
                //turn right
                myRobot->setRotVel(-5);
            }
            */
            int rotvel = (*myReadings)[95].getRange() - (*myReadings)[85].getRange();
            if (rotvel < -10) rotvel = -10;
            if (rotvel > 10) rotvel = 10;
            myRobot->setRotVel(rotvel/2);
        }

    } else {
        myLaser->asyncConnect();
    }

    myLaser->unlockDevice();
}
