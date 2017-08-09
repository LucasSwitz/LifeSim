collision_data = ...

correct_percent = .2
correct_threshold = .5
impulse_threshold = .1

DoImpulse = function(collision_data)
    collider_1 = collision_data.collider_1
    collider_2 = collision_data.collider_2

    norm = collision_data.norm
    collider_1_vel = {x = 0, y = 0}
    collider_2_vel = {x = 0, y = 0}

    if collider_2:HasComponent("Velocity") then    
        collider_2_vel = {
                            x = collider_2:GetNumber("Velocity","x"),
                            y = collider_2:GetNumber("Velocity","y")
                        }
    end

    relative_vel = {
                        x = collider_1_vel.x - collider_2_vel.x,
                        y = collider_1_vel.y - collider_2_vel.y
                   }

    collider_1_mass = collider_1:GetNumber("Mass","mass")
    collider_2_mass = collider_2:GetNumber("Mass","mass")

    vel_along_norm = Dot(relative_vel, norm)

    if vel_along_norm > 0 then
        return
    end

    restitution = .3

    impulse_scale = -(1 + restitution) * vel_along_norm

    impulse_scale = impulse_scale / (1.0 / collider_1_mass + 1.0/collider_2_mass)
    impulse = {x = norm.x*impulse_scale, 
               y = norm.y*impulse_scale}

    collider_2_vel.x = collider_2_vel.x - (1/collider_2_mass) * impulse.x 
    collider_2_vel.y = collider_2_vel.y - (1/collider_2_mass) * impulse.y
    
    if collider_2:HasComponent("Velocity") then
        if math.abs(collider_2_vel.y) < 4 then
            collider_2:SetNumber("Velocity","y",-.25*collision_data.overlap)
        else
            collider_2:SetNumber("Velocity","y",collider_2_vel.y)
        end

        if math.abs(collider_2_vel.x) < 0 then
            collider_2:SetNumber("Velocity","x",.005)
        else
            collider_2:SetNumber("Velocity","x",collider_2_vel.x)
        end
    end
end

Dot = function(v1, v2) 
    return v1.x*v2.x + v1.y*v2.y
end

Project = function(v1,v2)
    mag2 = Mag2(v1)
    dot = Dot(v1,v2)
    return {x = (v1.x*dot) / mag2, y = (v1.y*dot) / mag2}
end

Mag2 = function(v1)
    return v1.x*v1.x + v1.y*v1.y
end

if collision_data ~= nil then
    if collision_data.overlap > impulse_threshold then
        DoImpulse(collision_data)
    elseif collision_data.overlap > correct_threshold then
        
        return
    end
end
