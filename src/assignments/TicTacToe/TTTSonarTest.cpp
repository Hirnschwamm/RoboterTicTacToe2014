#include "TTTSonarTest.h"

TTTSonarTest::TTTSonarTest() : TicTacToeState(NULL, NULL)
{
}

TTTSonarTest::TTTSonarTest(ArRobot *myRobot, TicTacToeAction *action) : TicTacToeState(myRobot, action) {
    myLaser = myRobot->findLaser(1);
}

TTTSonarTest::~TTTSonarTest()
{

}

void TTTSonarTest::fire(ArActionDesired *currentDesired) {
    system("clear");
    /*
    for (int i = 0; i < myRobot->getNumSonar(); i++) {
        if (i < 10) printf(" ");
        printf("%i Sonar: %i\n", i, myRobot->getSonarRange(i));
    }
    */
    myLaser->lockDevice();

    printf("Has Laser %i, %i, %i\n", myRobot->hasLaser(myLaser), myLaser->isTryingToConnect(), myLaser->isConnected());
    std::vector<ArPoseWithTime> *myReadings = myLaser->getCurrentBufferAsVector();
    for (int i = 0; i < myReadings->size(); i++) {
        if (i % 5 > 0) continue;
        ArPoseWithTime curReading = (*myReadings)[i];
        if (i < 10) printf(" ");
        printf("%i reading: %ix%i\n", i, (int)curReading.getX(), (int)curReading.getY());
    }

    myLaser->unlockDevice();
}
