--PREAMBLE_START
ScriptType = "System"
Name = "StateSystem"
--PREAMBLE_END

package.path = package.path .. ";" .. Res("StateHelpers.lua")
helpers = require("StateHelpers")


STAGE_START = "Start"
STAGE_EXECUTE = "Execute"
STAGE_END = "End"

StateSystem = 
{
    Update = function(state_system, time, g)
    
        local entities = LuaListComponentUser()
        g:ComponentUsers():GetAll(entities,{"State"})
        local it = entities:Iterator()
        while it ~= nil do
            local current = it.data
            local current_state_time = current:GetNumber("State","time")
            current:SetNumber("State","time",current_state_time+time)
            state_file_name = current:GetString("State","state")
            local new_state = loadfile(state_file_name)(current,g,time) --TODO: potentially pass time here
             -- manages transition between state
            if new_state ~= nil then
                helpers.Switch(current,new_state,g)
            end
            it = it.next
        end
    end
    --[[EventHandler = 
    {
        GetSubscriptions  = function(state_system)
            return {Subscription(EventType.CHANGE_STATE_EVENT)}
        end
    }--]]
}