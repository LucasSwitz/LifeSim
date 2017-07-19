--PREAMBLE_START
ScriptType = "System"
Name = "GravitySystem"
--PREAMBLE_END


GravitySystem = 
{
    Update = function(movement_system, time)
        local physicals = LuaListComponentUser()
        ComponentUsers.Instance():GetAll(physicals,{"Position","Velocity","Acceleration"})
        local it = physicals:Iterator()
        while it ~= nil do
            user = it.data 
            cur_vel_y = user:GetNumber("Velocity","y")
            new_vel_y = cur_vel_y + 10
            user:SetNumber("Velocity","y",new_vel_y)
            it = it.next
        end 
    end

}