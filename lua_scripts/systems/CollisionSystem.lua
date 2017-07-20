--PREAMBLE_START
ScriptType = "System"
Name = "CollisionSystem"
--PREAMBLE_END

CollisionSystem = 
{
    --shitty O(n^2) collision detection 
    after = "GravitySystem",
    Update = function(self,time)
        local entities = LuaListComponentUser()
        ComponentUsers.Instance():GetAll(entities, {"Collision"})
        local it = entities:Iterator()
        while it ~= null do
            entity = it.data
            compare_it = it.next
            while compare_it ~= nil do
                compare = compare_it.data
                collision_data = self.GetCollision(entity, compare)
                if collision_data ~= nil then
                    --e = Event(EventType.COLLISION_EVENT, entity.id, compare.id)
                    --EventManager.Instance():LaunchEvent(e)
                    script_1 = entity:GetString("Collision","collision_script")
                    script_2 = compare:GetString("Collision", "collision_script")

                    if string.len(script_1) > 0 then
                        loadfile(script_1)(collision_data)
                    end

                    if string.len(script_2) > 0 then
                        loadfile(script_2)(collision_data)
                    end

                end
                compare_it = compare_it.next
            end
            it = it.next
        end
    end,
    CheckCollision = function(entity_1, entity_2)
        return (entity_1:GetNumber("Position","x")  < entity_2:GetNumber("Collision","width") 
                                                        + entity_2:GetNumber("Position","x")  and
                entity_2:GetNumber("Position","x")  < entity_1:GetNumber("Position","x") 
                                                        + entity_1:GetNumber("Collision","width") and
                entity_1:GetNumber("Position","y")  < entity_2:GetNumber("Position","y") 
                                                        + entity_2:GetNumber("Collision","height") and
                entity_2:GetNumber("Position","y")  < entity_1:GetNumber("Position","y") 
                                                        + entity_1:GetNumber("Collision","height"))
    end, 
    GetCollision = function(collider_1, collider_2)
        collider_1_pos = {x = collider_1:GetNumber("Position","x"),
                          y = collider_1:GetNumber("Position","y")}

        collider_2_pos = {x = collider_2:GetNumber("Position","x"),
                          y = collider_2:GetNumber("Position","y")}

        collider_1_dims = {width = collider_1:GetNumber("Collision","width"),
                           height = collider_1:GetNumber("Collision","height")}


        collider_2_dims = {width = collider_2:GetNumber("Collision","width"),
                           height = collider_2:GetNumber("Collision","height")}

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
                        return {
                                collider_1 = collider_1,
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