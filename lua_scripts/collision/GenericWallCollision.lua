collider_1, collider_2, time = ...

if collider_2:HasComponent("Velocity") then
    x_vel = collider_2:GetNumber("Velocity","x")
    y_vel = collider_2:GetNumber("Velocity","y")

    if math.abs(x_vel) > 0 then
        x_pos = collider_2:GetNumber("Position","x")
        collider_2:SetNumber("Position", "x", x_pos-(x_vel)*time)
        collider_2:SetNumber("Velocity", "x", 0)
    end

    if math.abs(y_vel) > 0 then
        y_pos = collider_2:GetNumber("Position","y")
        collider_2:SetNumber("Position", "y", y_pos-(y_vel)*time)
        collider_2:SetNumber("Velocity", "y", 0)
    end
end