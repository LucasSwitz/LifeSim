--PREAMBLE_START
ScriptType = "System"
Name = "HealthSystem"
--PREAMBLE_END

HEALTH_REGEN_PERIOD = 3 --seconds

HealthSystem = 
{
    total_time = 0.0,

    Update = function(health_system,time)
        health_system.total_time = health_system.total_time + time
        if health_system.total_time >= HEALTH_REGEN_PERIOD then
            health_system.total_time = 0
            health_system:Regenerate()
        end
        
    end,

    Regenerate = function()
        local entities = EntityManager.Instance():AsLuaList()
        local it = entities:Iterator()
        while it ~= nil do
            entity = it.data
            if entity:HasComponent("Health") then
                current_hp = entity:GetComponent("Health"):GetNumber("hp")
                entity:GetComponent("Health"):SetNumber("hp",current_hp + 10)
            end
            it = it.next
        end
    end
    
}