--PREAMBLE_START
ScriptType = "System"
Name = "CharacterIdleState"
--PREAMBLE_END

Stages = 
{
    Start = function(character)
        character:SetString("Animation","animation","Idle")
        character:SetNumber("Animation","stage",1)
    end,
    Execute = function(character)
        if KeyBoard.Instance():Get("W") ||
           KeyBoard.Instance():Get("A") ||
           KeyBoard.Instance():Get("S") ||
           KeyBoard.Instance():Get("D") then
            return "/home/pabu/Desktop/LifeSim/lua_scripts/states/character_state/CharacterWalkingState.lua"
        end
    end,
    End = function(character)
    end
}

character = ...

stage = character:GetNumber("State","stage")
Stages[stage](character)
