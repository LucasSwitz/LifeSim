--PREAMBLE_START
ScriptType = "System"
Name = "CharacterJumpState"
--PREAMBLE_END

Stages = 
{
    Start = function(character)
        character:SetString("Animation","animation","Idle")
        character:SetBool("Animation","started",false)

        character:SetString("State","stage","Execute")
        character:SetNumber("Velocity","y",-200)
    end,
    Execute = function(character)
        if character:GetNumber("Velocity","y") == 0 then
            return "/home/pabu/Desktop/LifeSim/lua_scripts/states/character_state/CharacterIdleState.lua"
        end
    end,
    End = function(character)
    end
}

character = ...

if character ~= nil then
    local stage = character:GetString("State","stage")
    return Stages[stage](character)
end
