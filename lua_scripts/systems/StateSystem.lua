--PREAMBLE_START
ScriptType = "System"
Name = "StateSystem"
--PREAMBLE_END

STAGE_START = "Start"
STAGE_EXECUTE = "Execute"
STAGE_END = "End"

StateSystem = 
{
    Update = function(state_system, time)
    
        local entities = ComponentUsers.Instance():GetAll{"State"}
        local it = entities:Iterator()
        while it ~= nil do
            local current = it.data
            state_file_name = current:GetString("State","state")
            local new_state = loadfile(state_file_name)(current)
            -- manages transition between state
            if new_state ~= nil then
                current:SetString("State","stage",STAGE_END) 
                loadfile(state_file_name)(current) --call end on old state 
                current:SetString("State","state",new_state) -- set new state
                current:SetString("State","stage",STAGE_START) -- set STAGE_START
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