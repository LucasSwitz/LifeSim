--PREAMBLE_START
ScriptType = "System"
Name = "CollisionSystem"
--PREAMBLE_END

CollisionSystem = 
{
    --shitty O(n^2) collision detection 
    Update = function(self,time)
        local entities = LuaListComponentUser()
        ComponentUsers.Instance():GetAll(entities,{"Collision"})
        local it = entities:Iterator()
        while it ~= null do
            entity = it.data
            compare_it = it.next
            while compare_it ~= nil do
                compare = compare_it.data
                if self.CheckCollision(entity, compare) then
                    e = Event(EventType.COLLISION_EVENT, entity.id, compare.id)
                    EventManager.Instance():LaunchEvent(e)
                    --if entity:IsType(Entity.LUA_DEFINED_ENTITY) then
                        --lua_entity = LuaEntity.Downcast(entity)
                        script_1 = entity:GetString("Collision","collision_script")
                        script_2 = compare:GetString("Collision", "collision_script")

                        if string.len(script_1) > 0 then
                            loadfile(script_1)(entity, compare, time)
                        end

                        if string.len(script_2) > 0 then
                            loadfile(script_2)(compare, entity, time)
                        end
                    --end 
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
    end 
}