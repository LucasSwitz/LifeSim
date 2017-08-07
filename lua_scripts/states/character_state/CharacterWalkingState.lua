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
        --look for keypress up or attack button, call end, set new state

        y = true 
        x = true
        if Keyboard.Instance():Get("W") then
            character:SetNumber("Velocity","heading",90)
            character:SetNumber("Velocity","y", -100)
        elseif Keyboard.Instance():Get("S") then
            character:SetNumber("Velocity","heading",270)
            character:SetNumber("Velocity","y", 100)
        else
            y = false
            character:SetNumber("Velocity","y", 0)
        end

        if Keyboard.Instance():Get("A") then
            character:SetNumber("Velocity","heading",180)
            character:SetNumber("Velocity","x", -100)   
        elseif Keyboard.Instance():Get("D") then
            character:SetNumber("Velocity","heading",0)
            character:SetNumber("Velocity","x", 100)
        else
            x= false
            character:SetNumber("Velocity","x", 0)
        end
        
        if Keyboard.Instance():Get("E") then
            return "/home/lucas/Desktop/LifeSim/lua_scripts/states/character_state/CharacterAttackingState.lua"  
        elseif not x and not y then
            return "/home/lucas/Desktop/LifeSim/lua_scripts/states/character_state/CharacterIdleState.lua"   
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