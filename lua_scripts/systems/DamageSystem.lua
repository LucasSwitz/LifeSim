--PREAMBLE_START
ScriptType = "System"
Name = "DamageSystem"
--PREAMBLE_END


DamageSystem = 
{
    EventHandler = 
    {
        OnEvent = function(event)
            attacked_entity =  EntityManager.Instance():Get(event.target)
            attacking_entity = EntityManager.Instance():Get(event.source)

            if(attacked_entity:HasComponent("Health")) then
                damage_done = event:ExtraInfoAsInt()
                attacked_entity:AsTable()["Components"]["Health"]["OnDamage"](damage_done)
            end
        end,
        GetSubscriptions = function()

            return {Subscription(EventType.DAMAGE_EVENT)}
        end
    }
}