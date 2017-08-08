--PREAMBLE_START
ScriptType = "System"
Name = "GravitySystem"
--PREAMBLE_END


GravitySystem = 
{
    after = "StateSystem",
    Update = function(movement_system, time)
        local physicals = LuaListComponentUser()
        ComponentUsers.Instance():GetAll(physicals,{"Mass","Position","Velocity","Acceleration"})
        local it = physicals:Iterator()
        while it ~= nil do
            user = it.data 
            cur_mass = user:GetNumber("Mass","mass")
            cur_vel_y = user:GetNumber("Velocity","y")
            new_vel_y = cur_vel_y + 1*cur_mass
            user:SetNumber("Velocity","y",new_vel_y)
            it = it.next
        end 
    end

}