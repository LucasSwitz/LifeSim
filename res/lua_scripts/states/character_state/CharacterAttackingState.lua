--PREAMBLE_START
ScriptType = "System"
Name = "CharacterAttackingState"
--PREAMBLE_END

Stages = 
{
    Start = function(character)
        character:SetString("Animation","animation","Idle")
        character:SetBool("Animation","started",false)
        character:SetString("State","stage","Execute")
    end,
    Execute = function(character,gs)
        loadfile(Res("ActionShootFireball.lua"))(gs,character)
        return Res("CharacterIdleState.lua")
    end,
    End = function(character)

    end
}

gs,character = ...

if character ~= nil and gs ~= nil then
    local stage = character:GetString("State","stage")
    return Stages[stage](character,gs)
end
