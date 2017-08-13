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
        character:SetNumber("Velocity","y",-300)
    end,
    Execute = function(character)
        if Keyboard.Instance():Get(Keyboard.A) then
            character:SetNumber("Position","heading",180)
            character:SetNumber("Velocity","x", -100)   
            character:SetBool("Graphics","invert",true)
        elseif Keyboard.Instance():Get(Keyboard.D) then
            character:SetNumber("Position","heading",0)
            character:SetNumber("Velocity","x", 100)
            character:SetBool("Graphics","invert",false)
        else
            x = false
            character:SetNumber("Velocity","x", 0)
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
