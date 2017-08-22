#include "src/game/tools/SpacialPartitioningGrid.h"
#include "src/world/stage/Instance.h"

SpacialPartitioningGrid::SpacialPartitioningGrid(Instance *i)
{
    int row_count = i->GetTileMap().WidthPx() / CELL_SIZE;
    int column_count = i->GetTileMap().HeightPx() / CELL_SIZE;

    for (int i = 0; i < row_count; i++)
    {
        _grid.push_back(std::vector<std::unordered_set<ComponentUser *>>());
        for (int k = 0; k < column_count; k++)
        {
            _grid[i].push_back(std::unordered_set<ComponentUser *>());
        }
    }
}

void SpacialPartitioningGrid::OnEvent(Event &e)
{
    if (e.id == EventType::COMPONENT_USER_MOVE_EVENT)
    {
        std::vector<float> *data = e.InfoToType<std::vector<float> *>();
        int component_user_id = e.target_id;
        ComponentUser *c = ComponentUserBase::Instance()->GetComponentUser(component_user_id);
        int old_column = GetColumn((*data)[0]);
        int old_row = GetRow((*data)[1]);
        int new_column = GetColumn((*data)[2]);
        int new_row = GetRow((*data)[3]);

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
    int row = GetRow(c->GetComponentValueFloat("Position", "y"));
    int column = GetRow(c->GetComponentValueFloat("Position", "x"));
    AddColliderToCell(c, row, column);
}

void SpacialPartitioningGrid::RemoveCollider(ComponentUser *c)
{
    int row = GetRow(c->GetComponentValueFloat("Position", "y"));
    int column = GetColumn(c->GetComponentValueFloat("Position", "x"));
    RemoveColliderFromCell(c, row, column);
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

std::unordered_set<ComponentUser *> &SpacialPartitioningGrid::GetAllInCell(int row, int column)
{
    return _grid[row][column];
}

bool SpacialPartitioningGrid::HasCollider(ComponentUser *user)
{
    int row = GetRow(user->GetComponentValueBool("Position", "y"));
    int column = GetColumn(user->GetComponentValueFloat("Position", "x"));

    return _grid[row][column].find(user) != _grid[row][column].end();
}

std::unordered_set<ComponentUser *> &SpacialPartitioningGrid::GetAllInSameCell(ComponentUser *user)
{
    int row = GetRow(user->GetComponentValueBool("Position", "y"));
    int column = GetColumn(user->GetComponentValueFloat("Position", "x"));

    return GetAllInCell(row, column);
}

int SpacialPartitioningGrid::GetColumn(int x_pos)
{
    return (y_pos - _anchor_point.x) / CELL_SIZE;
}

int SpacialPartitioningGrid::GetRow(int y_pos)
{
    return (x_pos - _anchor_point.y) / CELL_SIZE;
}
