--PREAMBLE_START
ScriptType = "System"
Name = "LifetimeSystem"
--PREAMBLE_END

LifetimeSystem = 
{
    Update = function(state_system, time, g)
    
        local entities = LuaListComponentUser()
        ComponentUsers.Instance():GetAll(entities,{"Lifetime"})
        local it = entities:Iterator()
        while it ~= nil do
            local current = it.data
            current_lifetime = current:GetNumber("Lifetime","time")
            if current_lifetime <= 0 then
                e = Event(EventType.DELETE_ENTITY_EVENT,-1,current.id)
            else
                current:SetNumber("Lifetime",current_lifetime-time);
            end

            it = it.next
        end
    end
}