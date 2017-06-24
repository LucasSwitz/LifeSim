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
            compare = it.next
            while compare ~= nil do
                if self.CheckCollision(entity, compare.data) then
                    EventManager.Instance():LaunchEvent(Event(EventType.COLLISION_EVENT, entity.id, compare.data.id, nil))
                    --entity:AsTable()["Components"]["Collision"]["OnCollision"](entity,compare)
                    --compare:AsTable()["Components"]["Collision"]["OnCollision"](compare,entity)
                end
                compare = compare.next
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