
SpawnFireball = function(user)
    FIREBALL_ENTITY_ID = 111

    e = Event.EntityEvent(EventType.SPAWN_ENTITY_EVENT,-1,FIREBALL_ENTITY_ID,fireball)
    MessageDispatch.Instance():LaunchEvent(e)

    fireball = EntityManager.Instance():Last() --has to be done like this because of LuaBridge

    fireball:SetNumber("Position","x", user:GetNumber("Position","x")+user:GetNumber("Collision","width")+2)
    fireball:SetNumber("Position","y", user:GetNumber("Position","y"))
    
    fireball:SetNumber("Velocity","x",30)
end

user = ...

if user~=nil then
    SpawnFireball(user)
end