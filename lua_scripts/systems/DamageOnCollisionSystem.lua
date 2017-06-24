--PREAMBLE_START
ScriptType = "System"
Name = "DamageOnCollisionSystem"
--PREAMBLE_END

DamageOnCollisionSystem = 
{
    EventHandler = 
    {
        OnEvent = function(self, event)
        

        end,
        GetSubscriptions = function()
        
            return { Subscription(EventType.COLLISION_EVENT) }
        end
    }
}