#include "TurnTo.h"
#include <TicTacToeAction.h>

TurnTo::TurnTo()
{
}

TurnTo::TurnTo(ArRobot *robot, ArACTS_1_2* acts){
    this->myRobot = robot;
    this->acts = acts;
    this->targetBlobIndex = -1;
}

bool TurnTo::fire(){
    if(acts->isConnected()){
        acts->getBlob(PLAYERPIECESCHANNEL, targetBlobIndex, &blob);

        int margin = 1;
        int xcg = blob.getXCG();
        int halfScreenW = SCREENWIDTH / 2;
        int turnSpeed = 3.0;
        if(xcg > (halfScreenW - margin) && xcg < (halfScreenW + margin)){
            myRobot->setRotVel(0.0);
            return true;
        //Object is not centered and robot position needs to be adjusted
        }else if(xcg > (halfScreenW - margin) && xcg > (halfScreenW + margin)){
          myRobot->setRotVel(-turnSpeed);
        }else if(xcg < (halfScreenW - margin) && xcg < (halfScreenW + margin)){
           myRobot->setRotVel(turnSpeed);
        }


    }

    return false;
}

