#ifndef EVENTTYPE_H
#define EVENTTYPE_H

/**
  EventType definitions
**/
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
    static int W_DOWN_EVENT;
    static int W_UP_EVENT;
    static int A_DOWN_EVENT;
    static int A_UP_EVENT;
    static int S_DOWN_EVENT;
    static int S_UP_EVENT;
    static int D_DOWN_EVENT;
    static int D_UP_EVENT;
    static int CLOSE_WINDOW_EVENT;
    static int CHANGE_INSTANCE_EVENT;
    static int EXIT_STAGE_EVENT;
    static int DRAW_REQUEST_EVENT;
    static int SPAWN_ENTITY_EVENT_PROTOTYPE;
    static int E_DOWN_EVENT;
    static int E_UP_EVENT;
    static int STOP_PROGRAM_EVENT;
    static int RECENTER_VIEW_EVENT;
    static int SPAWN_ENTITY_EVENT;
    static int ENTITY_SPAWNED_EVENT;
    static int START_SYSTEM_EVENT;
    static int STOP_SYSTEM_EVENT;
    static int STAGE_INSTANCE_CHANGING;
    static int STAGE_INSTANCE_CHANGED;
    static int COMPONENT_USER_MOVE_EVENT;

};
#endif