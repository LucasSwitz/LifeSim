
SpawnRock = function(user)
    ROCK_ENTITY_ID = 1000

    rock = EntityFactory.Instance():Get(ROCK_ENTITY_ID)

    rock:SetNumber("Position","x", user:GetNumber("Position","x")+user:GetNumber("Collision","width")+2)
    rock:SetNumber("Position","y", user:GetNumber("Position","y"))
    
    rock:SetNumber("Velocity","x",10)

    e = Event.EntityEvent(EventType.SPAWN_ENTITY_EVENT,-1,-1,rock)

    MessageDispatch.Instance():LaunchEvent(e)
end

user = ...

if user~=nil then
    SpawnRock(user)
end