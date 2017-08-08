package.path = package.path .. ";" .. Res("StateHelpers.lua")
helpers = require("StateHelpers")

collision_data = ...

if collision_data ~= nil then
    character = collision_data.collider_1 
    if character:GetString("State","state") == Res("CharacterJumpState.lua")
        and character:GetNumber("State","time") > .1 then
        if collision_data.norm.y == 1 then
            helpers.Switch(character,Res("CharacterIdleState.lua"))
        end
    end
end