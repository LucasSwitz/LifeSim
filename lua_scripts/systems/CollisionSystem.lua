--PREAMBLE_START
ScriptType = "System"
Name = "CollisionSystem"
--PREAMBLE_END

CollisionSystem = 
{
    --shitty O(n^2) collision detection 
    Update = function(self,time)
        local entities = ComponentUsers.Instance():GetAllEntities("Collision")
        local it = entities:Iterator()
        while it ~= null do
            entity = it.data
            compare_it = it.next
            while compare_it ~= nil do
                compare = compare_it.data
                if self.CheckCollision(entity, compare) then
                    EventManager.Instance():LaunchEvent(Event(EventType.COLLISION_EVENT, entity.id, compare.id, nil))
                    if entity:IsType(Entity.LUA_DEFINED_ENTITY) then
                        lua_entity = LuaEntity.Downcast(entity)
                        script = lua_entity:GetString("Collision","collision_script")
                        loadfile(script)(entity.id, compare.id)
                    end 
                    if compare:IsType(Entity.LUA_DEFINED_ENTITY) then
                        lua_entity = LuaEntity.Downcast(compare)
                        script = lua_entity:GetString("Collision","collision_script")
                        loadfile(script)(compare.id, entity.id)
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
    end 
}