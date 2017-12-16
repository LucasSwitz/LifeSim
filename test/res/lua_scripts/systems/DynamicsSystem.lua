--PREAMBLE_START
ScriptType = "System"
Name = "DynamicsSystem"
--PREAMBLE_END


DynamicsSystem = 
{
    after = "CollisionSystem",
    Update = function(dynamics_system, seconds_elapsed, g)
        local physicals = LuaListComponentUser()
        g:ComponentUsers():GetAll(physicals,{"Position","Velocity","Acceleration","Mass"})
        local it = physicals:Iterator()
        while it ~= nil do
            local current = it.data
            local position_x = current:GetNumber("Position","x")
            local position_y = current:GetNumber("Position","y")
            local mass =  current:GetNumber("Mass","mass")
            local force_x = current:GetNumber("Acceleration","force_x")
            local force_y = current:GetNumber("Acceleration","force_y")
            local velocity_x = current:GetNumber("Velocity","x")
            local velocity_y = current:GetNumber("Velocity","y")

            
            local accleration_x = force_x / mass
            local accleration_y = force_y / mass

            max_velocity = current:GetNumber("Velocity","max")

            velocity_x = velocity_x + accleration_x*seconds_elapsed
            velocity_y = velocity_y + accleration_y*seconds_elapsed
            
            --[[if math.abs(velocity_x) > max_velocity and velocity_x < 0 then
                velocity_x = -max_velocity
           -- elseif math.abs(velocity_x) > max_velocity and velocity_x > 0 then
                velocity_x = max_velocity
            --end-]]

            --[[if math.abs(velocity_y) > max_velocity and velocity_y < 0 then
                velocity_y = -max_velocity
            --elseif math.abs(velocity_y) > max_velocity and velocity_y > 0 then
                velocity_y = max_velocity
            --end--]]

            position_x = position_x + velocity_x*seconds_elapsed
            position_y = position_y + velocity_y*seconds_elapsed

            current:SetNumber("Velocity","x",velocity_x)
            current:SetNumber("Velocity","y",velocity_y)

            current:SetNumber("Position","x",position_x)
            current:SetNumber("Position","y",position_y)

            current:SetNumber("Acceleration","force_x",0)
            current:SetNumber("Acceleration","force_y",0)

            it = it.next
        end
    end
}