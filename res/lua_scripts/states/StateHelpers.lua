
STAGE_START = "Start"
STAGE_EXECUTE = "Execute"
STAGE_END = "End"

local helpers = {}

function helpers.Switch(state_owner,new_state)
        state_file_name = state_owner:GetString("State","state")
        state_owner:SetString("State","stage",STAGE_END) 
        loadfile(state_file_name)(state_owner) --call end on old state 
        state_owner:SetString("State","state",new_state) -- set new state
        state_owner:SetString("State","stage",STAGE_START) -- set STAGE_START
        state_owner:SetNumber("State","time",0)
end

return helpers