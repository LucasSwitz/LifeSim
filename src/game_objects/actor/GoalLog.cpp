    #include "GoalLog.h"

    bool GoalLog::operator < (const GoalLog& goal_log)
    {
        return GoalBase::Instance()->GetGoal(goal_name)->Priority(actor) < GoalBase::Instance()->GetGoal(goal_log.goal_name)->Priority(actor);
    }