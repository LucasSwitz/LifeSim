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
    Execute = function(character)
        loadfile(Res("ActionShootFireball.lua"))(character)
        return Res("CharacterIdleState.lua")
    end,
    End = function(character)

    end
}

character = ...

if character ~= nil then
    local stage = character:GetString("State","stage")
    return Stages[stage](character)
end