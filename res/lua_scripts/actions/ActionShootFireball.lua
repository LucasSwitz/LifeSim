
SpawnFireball = function(user)
    FIREBALL_ENTITY_ID = 111

    e = Event.EntityEvent(EventType.SPAWN_ENTITY_EVENT,-1,FIREBALL_ENTITY_ID,fireball)
    MessageDispatch.Instance():LaunchEvent(e)

    fireball = EntityManager.Instance():Last() --has to be done like this because of LuaBridge
    user_position = 
    {
        x = user:GetNumber("Position","x"),
        y = user:GetNumber("Position","y")
    }

    heading = user:GetNumber("Position","heading")

    direction = 
    {
            x = math.cos(math.rad(heading)),
            y = math.sin(math.rad(heading))   
    }

    fireball:SetNumber("Position","x", user_position.x+(user:GetNumber("Collision","width")+2)*direction.x)
    fireball:SetNumber("Position","y", user_position.y)
    
    fireball:SetNumber("Velocity","x",30*direction.x)
    fireball:SetNumber("Velocity","y",30*direction.y)

    if direction.x == -1 then
        fireball:SetBool("Graphics","invert",true)
    end

end

user = ...

if user~=nil then
    SpawnFireball(user)
end