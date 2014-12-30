#include "TTTPlacing.h"
#include<vector>

TTTPlacing::TTTPlacing() : TicTacToeState(NULL, NULL) {
    action->getField()->aiTurn(1, &targetX, &targetY);
    myState = 0;
}

TTTPlacing::TTTPlacing(ArRobot* myRobot, TicTacToeAction* action) :
    TicTacToeState(myRobot, action){
        myState = 0;

        gripper = new ArGripper(myRobot);
        //generate path
        start.x = myRobot->getPose().getX();
        start.y = myRobot->getPose().getY();

        int tmpTargetX = targetX;
        int tmptargetY = targetY;
        while (tmpTargetX == 1 && tmptargetY == 1) action->getField()->randomEmpty(&tmpTargetX, &tmptargetY);
        end.x = action->getWaypoints()->at(tmpTargetX).at(tmptargetY).x;
        end.y = action->getWaypoints()->at(tmpTargetX).at(tmptargetY).y;
        std::vector<WayPoint*> path;
        std::vector<WayPoint*> bestPath;
        finalPath.clear();

        WayPoint first(-1, -1, -1);
        PathUtil::findNextWp(start.x, start.y, &first, action->getWaypoints());

        WayPoint last(-1, -1, -1);
        PathUtil::findNextWp(end.x, end.y, &last, action->getWaypoints());

        path.push_back(&action->getWaypoints()->at(first.x).at(first.y));
        PathUtil::findPath(path[0], &action->getWaypoints()->at(last.x).at(last.y), &path, &bestPath);
        //finalPath.push_back(&start);
        for (int i = 0; i < bestPath.size(); i++) finalPath.push_back(bestPath[i]);
        finalPath.push_back(&end);

        WayPoint *center = &action->getWaypoints()->at(1).at(1);
        WayPoint dPos(center->x - end.x, center->y - end.y, -1);
        if (targetX == 1 && targetY == 1) {
            pPos.x = end.x + (dPos.x * .8);
            pPos.y = end.y + (dPos.y * .8);
        } else {
            pPos.x = end.x + (dPos.x * .25);
            pPos.y = end.y + (dPos.y * .25);
        }

        finalPath.push_back(&pPos);

        for (int i = 0; i < finalPath.size(); i++) {
            printf("%i. WP: %ix%i\n", i, (int) finalPath[i]->x, finalPath[i]->y);
        }

        myGoto = new GoTo(&finalPath, myRobot, false);
}

void TTTPlacing::fire(ArActionDesired *currentDesired){
    switch(myState) {
    case 0: { //getting in position for placeing
        if (myGoto->fire(currentDesired)) myState++;
        break;
    }

    case 1: { //place token
        gripper->gripperDeploy();
        myState++;
        break;
    }

    case 2: { // waiting for deploy to finish
        if (!gripper->isLiftMoving() && !gripper->isGripMoving() && gripper->isLiftMaxed()) myState++;
    }

    case 3: {
        ArPose myPose = myRobot->getPose();
        ArPose *lastPose = finalPath.at(finalPath.size() -1);
        if (myPose.findDistanceTo(*lastPose) < 200) {
            myRobot->setVel(-50);
        } else {
            myRobot->setVel(0);
            myState++;
        }
        break;
    }

    case 4: { //change state
        printf("Placeing Done.");
        myState++;
        action->setState(new TTTReturning(myRobot, action));
        break;
    }

    case 5: {
        printf("Not to be printed");
        break;
    }
    }
}
