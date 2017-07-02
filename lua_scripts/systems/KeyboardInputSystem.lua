--PREAMBLE_START
ScriptType = "System"
Name = "KeyboardInputSystem"
--PREAMBLE_END


KeyboardInputSystem = 
{
    OnEvent = function(keyboard_system, event)
        if event.id == EventType.W_DOWN_EVENT then
            local character = EntityManager.Instance():Get(0)
            local force_y = character:GetNumber("Acceleration","force_y")
            force_y= force_y + 10
            character:SetNumber("Acceleration","force_y",force_y)
        else if event.id == EventType.W_UP_EVENT then
            character:SetNumber("Velocity","y",0)
        else if event.id == EventType.S_DOWN_EVENT then
            local character = EntityManager.Instance():Get(0)
            local force_y = character:GetNumber("Acceleration","force_y")
            force_y= force_y - 10
            character:SetNumber("Acceleration","force_y",force_y)
        else if event.id == EventType.S_UP_EVENT then
            character:SetNumber("Velocity","y",0)
        end
    end

    GetSubscriptions = function(system)
        return {
                Subscription(EventType.W_DOWN_EVENT),
                Subscription(EventType.W_UP_EVENT),
                Subscription(EventType.S_DOWN_EVENT),
                Subscription(EventType.S_UP_EVENT)
                }
    end
}