#include <unordered_map>
#include "src/game_object/Entity.h"
#include "src/game_object/actor/GoalLog.h"

class Actor : public Entity{

public:

unsigned short getHunger() const
{
    return _hunger;
}



protected:
    unsigned short _age;
    unsigned short _health;
    unsigned short _hunger;
    std::unordered_map<std::string, int> _conditions;
    std::unordered_map<std::string, GoalLog*> _goals;
}