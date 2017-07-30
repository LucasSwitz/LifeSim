collision_data = ...

if collision_data ~= nil then
    fireball_id = collision_data.collider_1.id
    e = Event(EventType.DELETE_ENTITY_EVENT,fireball_id,-1)
    MessageDispatch.Instance():LaunchEvent(e)
do