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
    static int CLOSE_GAME_WINDOW_EVENT;
    static int CHANGE_INSTANCE_EVENT;
    static int EXIT_STAGE_EVENT;
    static int DRAW_REQUEST_EVENT;

};
#endif