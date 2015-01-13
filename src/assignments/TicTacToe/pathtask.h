#ifndef PATHTASK_H
#define PATHTASK_H

#include <ArFunctor.h>
#include <ArPathPlanningTask.h>
#include <TicTacToeAction.h>
#include <TicTacToeState.h>

class ArRobot;
class TicTacToeAction;
class TicTacToeState;

class PathTask : public ArFunctor
{
public:
    PathTask(ArRobot *robot, ArPathPlanningTask *pathTask, ArMap *map, ArPose pose, TicTacToeAction* action);
    virtual void invoke();

    void setPose(ArPose p){
        goal = p;
    }

    bool isIdle(){
        return idle;
    }

    void setIdle(bool i){
        idle = i;
    }

    void setReturnState(TicTacToeState* s){
        this->returnState = s;
    }

protected:
    ArRobot *robot;
    ArPathPlanningTask *pathPlanningTask;
    std::list<ArMapObject *> goals;
    std::list<ArMapObject *>::iterator it;
    ArPathPlanningTask::PathPlanningState state;
    ArPathPlanningTask::PathPlanningState previousState;

    TicTacToeState* returnState;
    ArPose goal;
    TicTacToeAction* action;
    bool idle;
};

#endif // PATHTASK_H
