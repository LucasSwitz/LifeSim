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
    end,
    EventHandler 
    {
        OnEvent = function(event)
            --do something with the event
            sender = event.sender
            target = event.target

            if(event.type == EventType.COLLIDED_EVENT) then
                -- apply damage
                damage = event.sender.damage

                -- Check if sender and reciever are componentable and if so check if they have health components.
                -- then do this vv 
                LaunchEvent(Event(EventType.HEALTH_CHANGE_EVENT, sender, target, current_hp - damage))

                -- apply knockback - NO Do this in Physics System
                -- apply conditions - NO Do this in Condition system

            else if (event.type == EventType.HEALTH_CHANGE_EVENT) then
                entity = EntityManager_GetEntity(sender)
                new_hp = event.ExtraInfoAsInt()
                entity:GetComponent("Health"):SetNumber("hp", new_hp)
            end
        end

        GetSubscriptions = function(entity, event)
            return {Subscription(EventType:HEALTH_CHANGE_EVENT),
                    Subscription(EventType:COLLIDED_EVENT)} --something like this
        end
    }
}