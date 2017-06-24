#ifndef EVENTTYPE_H
#define EVENTTYPE_H

class EventType
{
  public:
    static int MAKE_THIS_EVENT_DURING_TEST;
    static int NEVER_MAKE_THIS_EVENT;
    static int HEALTH_UPDATE_EVENT;
    static int COLLISION_EVENT;
    static int DAMAGE_EVENT;
    static int CONDITION_ADD_EVENT;
    static int DELETE_ENTITY_EVENT;
};

int EventType::MAKE_THIS_EVENT_DURING_TEST = -2;
int EventType::NEVER_MAKE_THIS_EVENT = -1;
int EventType::HEALTH_UPDATE_EVENT = 0;
int EventType::COLLISION_EVENT = 1;
int EventType::DAMAGE_EVENT = 2;
int EventType::CONDITION_ADD_EVENT = 3;
int EventType::DELETE_ENTITY_EVENT = 4;

#endif