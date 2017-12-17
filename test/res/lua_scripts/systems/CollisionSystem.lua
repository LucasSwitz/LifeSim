--PREAMBLE_START
ScriptType = "System"
Name = "CollisionSystem"
--PREAMBLE_END

CollisionSystem = 
{
    --shitty O(m*n) collision detection 
    after = "GravitySystem",
    Update = function(self,time, gs)
        local entities = LuaListEntity()
        local colliders = LuaListComponentUser()

        gs:ComponentUsers():GetAllEntities(entities,"Collision")
        gs:ComponentUsers():GetAll(colliders, {"Collision"})
        local entity_it = entities:Iterator()
        while entity_it ~= nil do            
            entity = entity_it.data
            collider_it = colliders:Iterator()
            while collider_it ~= nil do
                collider = collider_it.data
                if collider.id ~= entity.id then
                    collision_data = self.GetCollision(collider,entity,time)
                    if collision_data ~= nil then
                        collision_data.gs = gs                        
                        script_1 = entity:GetString(   "Collision", "collision_script")
                        script_2 = collider:GetString( "Collision", "collision_script" )

                        if string.len(script_1) > 0 then
                            collision_data.collider_1 = entity
                            collision_data.collider_2 = collider
                            loadfile(script_1)(collision_data)
                        end

                        if string.len(script_2) > 0 then
                            collision_data.collider_1 = collider
                            collision_data.collider_2 = entity
                            loadfile(script_2)(collision_data)
                        end

                        e = Event(EventType.COLLISION_EVENT, entity.id, collider.id)
                        gs:Msg():LaunchEvent(e)
                    end
                end
                collider_it = collider_it.next
            end
            entity_it = entity_it.next
        end
    end,
    GetCollision = function(collider_1, collider_2, time)
        collider_1_dims = {width = collider_1:GetNumber("Collision","width"),
                           height = collider_1:GetNumber("Collision","height")}

        collider_2_dims = {width = collider_2:GetNumber("Collision","width"),
                           height = collider_2:GetNumber("Collision","height")}

        collider_1_pos = {x = collider_1:GetNumber("Position","x") + collider_1:GetNumber("Velocity","x")*time/2,
                          y = collider_1:GetNumber("Position","y") + collider_1:GetNumber("Velocity","y")*time/2}

        collider_2_pos = {x = collider_2:GetNumber("Position","x") + collider_2:GetNumber("Velocity","x")*time/2,
                          y = collider_2:GetNumber("Position","y") + collider_2:GetNumber("Velocity","y")*time/2}



        distance = {x = collider_1_pos.x - collider_2_pos.x, 
                    y = collider_1_pos.y - collider_2_pos.y}

        collider_1_ext_x = collider_1_dims.width / 2.0; 
        collider_2_ext_x = collider_2_dims.width / 2.0;

        x_overlap = collider_1_ext_x + collider_2_ext_x - math.abs(distance.x)

        if x_overlap > 0 then
            collider_1_ext_y = collider_1_dims.height / 2.0; 
            collider_2_ext_y = collider_2_dims.height / 2.0;

            y_overlap = collider_1_ext_y + collider_2_ext_y - math.abs(distance.y)

            if y_overlap > 0 then 
                if x_overlap > y_overlap  then
                    if(distance.y < 0) then
                        return {collider_1 = collider_1,
                                collider_2 = collider_2,
                                norm  = 
                                {
                                    x = 0,
                                    y = -1,
                                },
                                overlap = y_overlap,
                                distance = distance}
                    else 
                        return {collider_1 = collider_1,
                                collider_2 = collider_2,
                                norm  = 
                                {
                                    x = 0,
                                    y = 1,
                                },
                                overlap = y_overlap,
                                distance = distance}
                    end
                else
                    if distance.x < 0 then
                        return {collider_1 = collider_1,
                                collider_2 = collider_2,
                                norm  = 
                                {
                                    x = -1,
                                    y = 0,
                                },
                                overlap = x_overlap,
                                distance = distance}
                    else
                        return {collider_1 = collider_1,
                                collider_2 = collider_2,
                                norm  = 
                                {
                                    x = 1,
                                    y = 0,
                                },
                                overlap = x_overlap,
                                distance = distance}
                    end
                end 
            end
        end
    end
}