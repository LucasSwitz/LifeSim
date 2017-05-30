

void Actor::Tick()
{

}

void Actor::GetHunger(std::string goal_name)
{
    _goal_list.push_back(new GoalLog(goal_name,this));
}

int Actor::GetHunger()
{
    return _hunger;
}