#ifndef PATHTASK_H
#define PATHTASK_H

#include <ArFunctor.h>
#include <ArPathPlanningTask.h>
#include <TicTacToeAction.h>

class ArRobot;
class TicTacToeAction;

class PathTask : public ArFunctor
{
public:
    PathTask(ArRobot *robot, ArPathPlanningTask *pathTask, ArMap *map, ArPose pose, TicTacToeAction* action);
    virtual void invoke();

    void setPose(ArPose p){
        goal = p;
    }

protected:
    ArRobot *robot;
    ArPathPlanningTask *pathPlanningTask;
    std::list<ArMapObject *> goals;
    std::list<ArMapObject *>::iterator it;
    ArPathPlanningTask::PathPlanningState state;
    ArPathPlanningTask::PathPlanningState previousState;

    ArPose goal;
    TicTacToeAction* action;
};

#endif // PATHTASK_H
