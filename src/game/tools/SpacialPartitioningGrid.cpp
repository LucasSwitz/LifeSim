#include "src/game/tools/SpacialPartitioningGrid.h"
#include "src/world/stage/Instance.h"

SpacialPartitioningGrid::SpacialPartitioningGrid(Instance* i)
{
    int row_count = i->GetTileMap().WidthPx() / CELL_SIZE;
    int column_count = i->GetTileMap().HeightPx() / CELL_SIZE;

    for(int i = 0; i < row_count; i++)
    {
        _grid.push_back(std::vector<std::unordered_set<ComponentUser*>>());
        for(int k =0; k < column_count; k++)
        {
            _grid[i].push_back(std::unordered_set<ComponentUser*>());
        }
    }
}

void SpacialPartitioningGrid::OnEvent(Event &e)
{
    if (e.id == EventType::COMPONENT_USER_MOVE_EVENT)
    {
        std::vector<float> *data = e.InfoToType<std::vector<float> *>();
        int component_user_id = e.target_id;
        ComponentUser* c = ComponentUserBase::Instance()->GetComponentUser(component_user_id);
        int old_column = (*data)[0] / CELL_SIZE;
        int old_row = (*data)[1] / CELL_SIZE;
        int new_column = (*data)[2] / CELL_SIZE;
        int new_row = (*data)[3] / CELL_SIZE;

        if (old_column != new_column || old_row != new_row)
        {
            RemoveColliderFromCell(c, old_row, old_column);
            AddColliderToCell(c, new_row, new_column);
        }

        delete data;
    }
}

void SpacialPartitioningGrid::AddCollider(ComponentUser *c)
{
    int row = c->GetComponentValueFloat("Position", "x") / CELL_SIZE;
    int column = c->GetComponentValueFloat("Position", "y") / CELL_SIZE;
    AddColliderToCell(c,row, column);
}

void SpacialPartitioningGrid::RemoveCollider(ComponentUser *c)
{
    int row = c->GetComponentValueFloat("Position", "x") / CELL_SIZE;
    int column = c->GetComponentValueFloat("Position", "y") / CELL_SIZE;
    RemoveColliderFromCell(c,row, column);
}

void SpacialPartitioningGrid::RemoveColliderFromCell(ComponentUser *c, int row, int column)
{
    _grid[row][column].erase(_grid[row][column].find(c));
}

void SpacialPartitioningGrid::AddColliderToCell(ComponentUser *c, int row, int column)
{
    _grid[row][column].insert(c);
}

std::list<Subscription> SpacialPartitioningGrid::GetSubscriptions()
{
    std::list<Subscription> subs = {Subscription(EventType::COMPONENT_USER_MOVE_EVENT)};

    return subs;
}

void SpacialPartitioningGrid::OnEvent(ComponentUserBaseEvent &e)
{
    if (e.type == ComponentUserBaseEvent::ADD)
    {
        AddCollider(e.user);
    }
    else if (e.type == ComponentUserBaseEvent::REMOVE)
    {
        RemoveCollider(e.user);
    }
}

std::unordered_set<ComponentUser*>& SpacialPartitioningGrid::GetAllInCell(int row, int column)
{
    return _grid[row][column];
}

bool SpacialPartitioningGrid::HasCollider(ComponentUser* user)
{
    int row = user->GetComponentValueBool("Position","x") / CELL_SIZE;
    int column = user->GetComponentValueFloat("Position","y") / CELL_SIZE;

    return _grid[row][column].find(user) != _grid[row][column].end();
}

std::unordered_set<ComponentUser*>& SpacialPartitioningGrid::GetAllInSameCell(ComponentUser* user)
{
    int row = user->GetComponentValueBool("Position","x") / CELL_SIZE;
    int column = user->GetComponentValueFloat("Position","y") / CELL_SIZE;

    return GetAllInCell(row,column);
}



