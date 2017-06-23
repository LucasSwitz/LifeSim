--PREAMBLE_START
ScriptType = "System"
Name = "MovementSystem"
--PREAMBLE_END


MovementSystem = 
{
    Update = function(movement_system, time)
        local entities = ComponentManager.Instance():GetAll("Position","Velocity")
        
    end

}