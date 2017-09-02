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
        controller_id = character:GetNumber("Player","controller_id")
        controller = SSPIDowncast((GetController(controller_id)))

        if controller:Jump() then
            return Res("CharacterJumpState.lua")
        elseif controller:Left() or
               controller:Right() then
            return Res("CharacterWalkingState.lua")
        elseif controller:Action() then
            return Res("CharacterAttackingState.lua")
        end
    end,
    End = function(character)
    end
}

character,gs = ...

if character ~= nil and gs ~= nil then
    local stage = character:GetString("State","stage")
    return Stages[stage](character,gs)
end