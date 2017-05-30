    bool GoalLog::operator < (const GoalLog& goal_log)
    {
        return GoalBase::Instance()->GetGoal(_goal_name)->Priority(_actor) < GoalBase::Instance()->GetGoal(goal_log._goal_name)->Priority(_actor);
    }