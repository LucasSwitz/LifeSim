collision_data = ...

correct_percent = .2
correct_threshold = .5
impulse_threshold = .1

DoImpulse = function(collision_data)
    collider_2 = collision_data.collider_2
    norm = collision_data.norm
    collider_2_vel = {x = 0, y = 0}

    if collider_2:HasComponent("Velocity") then
        collider_2_vel = {
                            x = collider_2:GetNumber("Velocity","x"),
                            y = collider_2:GetNumber("Velocity","y")
                        }
    end

    vel_along_norm = Dot(collider_2_vel, norm)

    if vel_along_norm < 0 then
        return
    end
    
    projection = Project(collision_data.norm,collider_2_vel)

    collider_2_vel.x = collider_2_vel.x - projection.x
    collider_2_vel.y = collider_2_vel.y - projection.y
    if collider_2:HasComponent("Velocity") then
        if(math.abs(collider_2_vel.y) < 10)  then
            collider_2:SetNumber("Velocity","y",-.1*((norm.y + .1) + .5))
        else
            collider_2:SetNumber("Velocity","y",collider_2_vel.y)
        end
        if math.abs(collider_2_vel.x) < 10 then
            collider_2:SetNumber("Velocity","x",0)
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
