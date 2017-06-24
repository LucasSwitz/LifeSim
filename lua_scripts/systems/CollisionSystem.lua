--PREAMBLE_START
ScriptType = "System"
Name = "CollisionSystem"
--PREAMBLE_END

CollisionSystem = 
{
    Update = function(self)
        local entities = ComponentManager.Instance:GetAll("Collision")
        local it = entities:Iterator()

        while it ~= nil do
            entity = it.data
            collided, collided_with = CheckCollision(entity)
            if collided then
                entity:AsTable()["Components"]["Collision"]["OnCollision"](collided_with)
            it = it.next
        end
    
    end 
}