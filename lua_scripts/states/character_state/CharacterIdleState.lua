--PREAMBLE_START
ScriptType = "System"
Name = "CharacterIdleState"
--PREAMBLE_END

Stages = 
{
    Start = function(character)
        character:SetString("Animation","animation","Idle")
    end,
    Execute = function(character)

    end,
    End = function(character)
        --Check Keyboard input here and do stuff
    end
}

character = ...

stage = character:GetNumber("State","stage")
Stages[stage](character)
