#ifndef SPACIALPARTITIONINGSYSTEM_H
#define SPACIALPARTITIONINGSYSTEM_H

#include <unordered_set>

#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"
#include "src/component/ComponentUser.h"
#include "src/component/ComponentUserBase.h"
#include "src/utils/math/Point.h"

#define CELL_SIZE 30

class Instance;

class SpacialPartitioningGrid : public EventSubscriber, public ComponentUserBaseSubscriber
{

public:
    SpacialPartitioningGrid(Instance* i);

    void AddCollider(ComponentUser* c);
    void RemoveCollider(ComponentUser* c);

    void AddColliderToCell(ComponentUser* c, int row, int column);
    void RemoveColliderFromCell(ComponentUser* c, int row, int column);
    
    //Inherited from EventSubscriber
    void OnEvent(Event& e);
    std::list<Subscription> GetSubscriptions();

    //Inherited from ComponentUseBaseSubscriber
    void OnEvent(ComponentUserBaseEvent& e);

    std::unordered_set<ComponentUser*>& GetAllInCell(int row,int column);
    std::unordered_set<ComponentUser*>& GetAllInSameCell(ComponentUser* c);

    bool HasCollider(ComponentUser* user);
    //GetAllInSameCellLuaList(ComponentUser* c);
private:
    std::vector<std::vector<std::unordered_set<ComponentUser*>>> _grid;
    int GetColumn(int x_pos);
    int GetRow(int y_pos);
    Point _anchor_point;
};

#endif