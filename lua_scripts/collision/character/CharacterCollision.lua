collision_data = ...

if collision_data ~= nil then
    character = collision_data.collider_1 
    collider = collision_data.collider_2
    if character:GetString("State","state") is Res("CharacterJumpingState") then
        if collision_data.normal == 1 then
            character:SetString("State","state",Res("CharacterIdleState"))
            character:SetString("State","stage","Start")
        end
    end
end