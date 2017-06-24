--PREAMBLE_START
ScriptType = "Systemf"
Name = "MovementSystem"
--PREAMBLE_END


MovementSystem = 
{
    Update = function(movement_system, time)
        local entities = ComponentManager.Instance():GetAll("Position","Velocity")
        
    end

}