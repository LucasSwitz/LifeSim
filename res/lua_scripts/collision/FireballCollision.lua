collision_data = ...

if collision_data ~= nil then
    fireball = Entity.Downcast(collision_data.collider_1)
    fireball_id = fireball.id
    e = Event(EventType.DELETE_ENTITY_EVENT,-1,fireball_id)
    gs:Msg():LaunchEvent(e)
end