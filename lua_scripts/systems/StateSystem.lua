--PREAMBLE_START
ScriptType = "System"
Name = "StateSystem"
--PREAMBLE_END

STAGE_START = 0
STAGE_EXECUTE = 1
STAGE_END = 2

StateSystem = 
{
    Update = function(state_system, time)
    
        local entities = ComponentManager.Instance():GetAll{"State"}
        local it = entities:Iterator()

        while it ~= nil do
            local current = it.data
            local state_file_name = current:GetString("State","state")
            local new_state = dofile(state_file_name)(current)

            -- manages transition between state
            if new_state ~= nil then
                current:SetString("State","stage",STAGE_END) 
                dofile(state_file_name)(current) --call end on old state 
                current:SetString("State","state",new_state) -- set new state
                current:SetString("State","stage",STAGE_START) -- set STAGE_START
                dofile(stage_file_name)(current) -- do start stage
            end
        end
    end,
    EventHandler = 
    {
        GetSubscriptions  = function(state_system)
            return {Subscription(EventType.CHANGE_STATE_EVENT)}
        end
    }
}