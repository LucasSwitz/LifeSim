--PREAMBLE_START
ScriptType = "System"
Name = "KeyboardInputSystem"
--PREAMBLE_END

-- Applying a constant velocity rather than a force might be more intutive for a player
KeyboardInputSystem = 
{
    EventHandler  =
    {
        OnEvent = function(keyboard_system, event)
            local character = EntityManager.Instance():Get(0)
            if event.id == EventType.W_DOWN_EVENT then
                local force_y = -30
                character:SetNumber("Acceleration","force_y",force_y)
            elseif event.id == EventType.W_UP_EVENT then
                character:SetNumber("Velocity","y",0)
            elseif event.id == EventType.S_DOWN_EVENT then
                local force_y = character:GetNumber("Acceleration","force_y")
                force_y= 30
                character:SetNumber("Acceleration","force_y",force_y)
            elseif event.id == EventType.S_UP_EVENT then
                character:SetNumber("Velocity","y",0)
            end
        end,

        GetSubscriptions = function(system)
            return {Subscription(EventType.W_DOWN_EVENT),
                    Subscription(EventType.W_UP_EVENT),
                    Subscription(EventType.S_DOWN_EVENT),
                    Subscription(EventType.S_UP_EVENT)}
        end
    }
}