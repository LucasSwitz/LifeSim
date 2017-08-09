--PREAMBLE_START
ScriptType = "System"
Name = "CharacterWalkingState"
--PREAMBLE_END

Stages = 
{
    Start = function(character)
        character:SetString("Animation","animation","Walking")
        character:SetBool("Animation","started",false)

        character:SetString("State","stage","Execute")
    end,
    Execute = function(character)
        -- check which direction the key press is and apply force accordingly
        -- look for keypress up or attack button, call end, set new state

        if Keyboard.Instance():Get(Keyboard.W) then
            return Res("CharacterJumpState.lua")
        end

        x = true
        if Keyboard.Instance():Get(Keyboard.A) then
            character:SetNumber("Position","heading",180)
            character:SetBool("Graphics","invert",true)
            character:SetNumber("Velocity","x", -100)   
        elseif Keyboard.Instance():Get(Keyboard.D) then
            character:SetNumber("Position","heading",0)
            character:SetBool("Graphics","invert",false)
            character:SetNumber("Velocity","x", 100)
        else
            x = false
            character:SetNumber("Velocity","x", 0)
        end
        
        if Keyboard.Instance():Get(Keyboard.E) then
            return Res("CharacterAttackingState.lua") 
        elseif not x then
            return Res("CharacterIdleState.lua")   
        end
    end,
    End = function(character)
        character:SetNumber("Velocity","y", 0)
        character:SetNumber("Velocity","x", 0)
    end
}

character = ...

if character ~= nil then
    local current_stage = character:GetString("State","stage")
    return Stages[current_stage](character)
end