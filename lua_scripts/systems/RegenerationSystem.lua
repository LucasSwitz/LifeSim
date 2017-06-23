--PREAMBLE_START
ScriptType = "System"
Name = "RegenerationSystem"
--PREAMBLE_END

HEALTH_REGEN_PERIOD = 3 --seconds

RegenerationSystem = 
{
    total_time = 0.0,

    Update = function(self,time)
        self.total_time = self.total_time + time
        if self.total_time >= HEALTH_REGEN_PERIOD then
            self.total_time = 0
            self:RegenerateAll()
        end
        
    end,
    RegenerateAll = function()
        local entities = ComponentManager.Instance():GetAll("Health")
        local it = entities:Iterator()
        while it ~= nil do
            entity = it.data
            current_hp = entity:GetNumber("Health", "hp");
            LaunchEvent(Event(EventType.HEALTH_CHANGE_EVENT, nil, entity.id, current_hp + 10))
            it = it.next
        end
    end,
    Decorators =
    {
        EventHandler =
        {
            OnEvent = function(self,event)
                --do something with the event
                sender = event.sender
                target = event.target
                --[[if(event.type == EventType.COLLISION_EVENT) then
                    -- apply damage
                    damage = event.sender.damage

                    -- Check if sender and reciever are componentable and if so check if they have health components.
                    -- then do this vv 
                    LaunchEvent(Event(EventType.HEALTH_CHANGE_EVENT, sender, target, current_hp - damage))

                    -- apply knockback - NO Do this in Physics System
                    -- apply conditions - NO Do this in Condition system

                elseif (event.type == EventType.HEALTH_CHANGE_EVENT) then
                    entity = EntityManager_GetEntity(sender)
                    new_hp = event.ExtraInfoAsInt()
                    entity:GetComponent("Health"):SetNumber("hp", new_hp)
                end]]--
            end,

            GetSubscriptions = function()
                return {Subscription(EventType.HEALTH_UPDATE_EVENT),
                        Subscription(EventType.COLLISION_EVENT)}
            end
        }
    }
}