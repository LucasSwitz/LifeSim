#ifndef EVENTTYPE_H
#define EVENTTYPE_H

class EventType
{
  public:
    static int HEALTH_UPDATE_EVENT;
    static int COLLISION_EVENT;
};

int EventType::HEALTH_UPDATE_EVENT = 0;
int EventType::COLLISION_EVENT = 1;
#endif