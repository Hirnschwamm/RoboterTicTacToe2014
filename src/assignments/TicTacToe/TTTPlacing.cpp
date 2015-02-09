#include "TTTPlacing.h"
#include<vector>

TTTPlacing::TTTPlacing() : TicTacToeState(NULL, NULL) {
    myState = 0;
}

TTTPlacing::TTTPlacing(ArRobot* myRobot, TicTacToeAction* action) :
    TicTacToeState(myRobot, action){
        myState = 0;
        action->getField()->aiTurn(4, &targetX, &targetY);
        action->getField()->field[targetX][targetY] = action->getField()->turn() % 2;
        gripper = new ArGripper(myRobot);
        //generate path
        start.x = myRobot->getPose().getX();
        start.y = myRobot->getPose().getY();

        int tmpTargetX = targetX;
        int tmpTargetY = targetY;

        while (tmpTargetX == 1 && tmpTargetY == 1) action->getField()->randomEmpty(&tmpTargetX, &tmpTargetY);
        end.x = action->getWaypoints()->at(tmpTargetX).at(tmpTargetY).x;
        end.y = action->getWaypoints()->at(tmpTargetX).at(tmpTargetY).y;

        printf("Placing at %ix%i: %ix%i\n", targetX, targetY, end.x, end.y);

        std::vector<WayPoint*> path;
        std::vector<WayPoint*> bestPath;
        finalPath.clear();

        WayPoint first(-1, -1, -1);
        PathUtil::findNextWp(start.x, start.y, &first, action->getWaypoints());

        WayPoint last(-1, -1, -1);
        PathUtil::findNextWp(end.x, end.y, &last, action->getWaypoints());

        //add first WP to path
        path.push_back(&action->getWaypoints()->at(first.x).at(first.y));
        //compute path from first WP to last WP
        PathUtil::findPath(path[0], &action->getWaypoints()->at(last.x).at(last.y), &path, &bestPath);
        for (int i = 0; i < bestPath.size(); i++) finalPath.push_back(bestPath[i]);
        finalPath.push_back(bestPath[bestPath.size() - 1]);

        WayPoint *center = &action->getWaypoints()->at(1).at(1);
        WayPoint dPos(center->x - end.x, center->y - end.y, -1);
        if (targetX == 1 && targetY == 1) {
            pPos.x = end.x + (dPos.x * .7);
            pPos.y = end.y + (dPos.y * .7);
        } else {
            pPos.x = end.x + (dPos.x * .1);
            pPos.y = end.y + (dPos.y * .1);
        }
        //position for placeing
        finalPath.push_back(&pPos);

        for (int i = 0; i < finalPath.size(); i++) {
            printf("%i. WP: %ix%i\n", i, (int) finalPath[i]->x, finalPath[i]->y);
        }

        myGoto = new GoTo(&finalPath, myRobot, action, false);
}

void TTTPlacing::fire(ArActionDesired *currentDesired){
    printf("p(%i)>", ticks);
    switch(myState) {
    case 0: { //getting in position for placeing
        if (myGoto->fire(currentDesired)) myState++;
        break;
    }

    case 1: { //lower lift
        gripper->liftDown();
        ticks = 0;
        myState++;
        break;
    }

    case 2: { //place token
        if (ticks < 100) {
            ticks++;
        } else {
            ticks = 0;
            gripper->gripperDeploy();
            myState++;
        }
        break;
    }

    case 3: { // waiting for deploy to finish
        if (!gripper->isLiftMoving() && !gripper->isGripMoving() && gripper->isLiftMaxed()) myState++;
    }

    case 4: { //Moving away from token
        ArPose myPose = myRobot->getPose();
        ArPose lastPose = finalPath.at(finalPath.size() -1)->getPose();
        //if (myPose.findDistanceTo(lastPose) < 200) {
        if (ticks < 30) {
            printf("Moveing away from token...\n");
            ticks++;
            myRobot->setVel(-50);
        } else {
            ticks = 0;
            myRobot->setVel(0);
            myState++;
        }
        break;
    }

    case 5: { //change state
        printf("Placeing Done.");
        myState++;
        printf("STATETRANSITION: PLACEING--->RETURNING\n");
        action->setState(new TTTReturning(myRobot, action, finalPath.at(finalPath.size() - 2)));
        break;
    }

    case 6: {
        printf("Not to be printed");
        break;
    }
    }
}
