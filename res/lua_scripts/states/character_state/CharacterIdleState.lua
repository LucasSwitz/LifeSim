--PREAMBLE_START
ScriptType = "System"
Name = "CharacterIdleState"
--PREAMBLE_END

Stages = 
{
    Start = function(character)
        character:SetString("Animation","animation","Idle")
        character:SetBool("Animation","started",false)
        character:SetString("State","stage","Execute")
    end,
    Execute = function(character)
        if Keyboard.Instance():Get(Keyboard.W) then
            return Res("CharacterJumpState.lua")
        elseif Keyboard.Instance():Get(Keyboard.A) or
               Keyboard.Instance():Get(Keyboard.D) then
            return Res("CharacterWalkingState.lua")
        elseif Keyboard.Instance():Get(Keyboard.E) then
            return Res("CharacterAttackingState.lua")
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
