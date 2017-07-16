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
        if Keyboard.Instance():Get("W") or
           Keyboard.Instance():Get("A") or
           Keyboard.Instance():Get("S") or
           Keyboard.Instance():Get("D") then
            print("Walking")
            return "/home/pabu/Desktop/LifeSim/lua_scripts/states/character_state/CharacterWalkingState.lua"
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
