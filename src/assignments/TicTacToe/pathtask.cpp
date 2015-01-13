#include "pathtask.h"

#include <ArRobot.h>

PathTask::PathTask(ArRobot *robot, ArPathPlanningTask *pathTask, ArMap *map, ArPose pose, TicTacToeAction* action) :
    robot(robot),
    pathPlanningTask(pathTask),
    goals(map->findMapObjectsOfType("Goal", true)),
    state(ArPathPlanningTask::NOT_INITIALIZED),
    previousState(ArPathPlanningTask::NOT_INITIALIZED)
{
    printf("LOLOLOLOLO\n");
    this->goal = pose;
    this->action = action;
    pathPlanningTask->setMaxSpeed(50.0);
    idle = true;
    printf("LOLOLOLOLO2\n");
}


void PathTask::invoke()
{
    printf("LOLOLOLOLO3\n");
    if(!idle){
        char text[512];
        state = pathPlanningTask->getState();
        if (state != previousState) {
            pathPlanningTask->getStatusString(text, sizeof(text));
            ArLog::log(ArLog::Normal, "Planning status: %s.", text);
        }

        switch (state) {
            case ArPathPlanningTask::NOT_INITIALIZED: // Task not initialized
                if (goals.size() > 0)  {
                    pathPlanningTask->init();
                    it = goals.begin();
                    //pathPlanningTask->pathPlanToPose((*it)->getPose(), true);
                    pathPlanningTask->pathPlanToPose(goal, true);
                } else {
                    ArLog::log(ArLog::Terse, "Warning: Map contains no goals!");
                }
                printf("LOLOLOLOL4\n");
            break;
            case ArPathPlanningTask::PLANNING_PATH: // Planning the inital path
              //TODO: implement state
            printf("LOLOLOLOLO5\n");
            break;
            case ArPathPlanningTask::MOVING_TO_GOAL: // Moving to the goal
                //TODO: implement state
            printf("LOLOLOLOLO6\n");
            break;
            case ArPathPlanningTask::REACHED_GOAL: // Reached the goal
                idle = true;
                action->setReturnState(returnState);
                action->activate();
                //pathPlanningTask->pathPlanToPose((*it)->getPose(), false);
            break;
            case ArPathPlanningTask::FAILED_PLAN: // Failed to plan a path to goal
                //TODO: implement state
            printf("LOLOLOLOLO57\n");
            break;
            case ArPathPlanningTask::FAILED_MOVE: // Failed to reach goal after plan obtained
                //TODO: implement state
            printf("LOLOLOLOLO8\n");
            break;
            case ArPathPlanningTask::ABORTED_PATHPLAN: // Aborted plan before done
                //TODO: implement state
            printf("LOLOLOLOLO9\n");
            break;
            case ArPathPlanningTask::INVALID: // Invalid state
                //TODO: implement state
            printf("LOLOLOLOLO10\n");
            break;
        }
        previousState = state;
    }
}
