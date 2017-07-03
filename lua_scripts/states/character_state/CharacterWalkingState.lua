--PREAMBLE_START
ScriptType = "System"
Name = "CharacterWalkingState"
--PREAMBLE_END

Stages = 
{
    Start = function(character)
        character:SetString("Animation","animation","Walking")
        character:SetNumber("Animation","stage",1)
    end,
    Execute = function(character)
        -- check which direction the key press is and apply force accordingly
        --look for keypress up or attack button, call end, set new state
        if Keyboard.Instance():Get("W") then
            character:SetNumber("Acceleration","force_y", -10)
        elseif Keyboard.Instance():Get("S") then
            character:SetNumber("Acceleration","force_y", 10)
        elseif Keyboard.Instance():Get("A") then
            character:SetNumber("Acceleration","force_x", -10)   
        elseif Keyboard.Instance():Get("D") then
            character:SetNumber("Acceleration","force_x", 10)
        else
            return "/home/pabu/Desktop/LifeSim/lua_scripts/states/character_state/CharacterIdleState.lua"   
    end,
    End = function(character)
        
    end
}

character = ...
local current_stage = character:GetNumber("State","current_stage")
return Stages[current_stage](character)