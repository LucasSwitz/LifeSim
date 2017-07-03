--PREAMBLE_START
ScriptType = "System"
Name = "CharacterWalkingState"
--PREAMBLE_END

Stages = 
{
    Start = function(character)
        character:SetString("Animation","Walking")
    end,
    Execute = function(character)
        -- check which direction the key press is and apply force accordingly
        character:SetNumber("Acceleration","force_y", 10)
        --look for keypress up or attack button, call end, set new state

    end,
    End = function(character)
        
    end
}

character = ...
local current_stage = character:GetNumber("State","current_stage")
return Stages[current_stage](character)