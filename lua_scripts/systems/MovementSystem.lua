--PREAMBLE_START
ScriptType = "System"
Name = "MovementSystem"
--PREAMBLE_END

MovementSystem = 
{
    Update = function(movement_system, seconds_elapsed)
    
        local moveables = ComponentUsers.Instance():GetAll({"Position","Velocity"})
        local it = moveables:Iterator()

        while it ~= nil do
            local moveable = it.data
            local pos_x = moveable:GetNumber("Position","x")
            local velocity = moveable:GetNumber("Velocity","x")
            moveable:SetNumber("Position","x",pos_x + velocity*seconds_elapsed)

            it = it.next
        end

    end

}