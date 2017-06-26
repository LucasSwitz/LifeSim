--PREAMBLE_START
ScriptType = "Entity"
Name = "CollisionTestEntity2"
PrototypeID = 1003
--PREAMBLE_END

CollisionTestEntity2 = 
{
    Components = {
        Position =
        {
            x = 5,
            y = 10
        },
        Collision = 
        {
            width = 10,
            height = 10,
            collider = -1,
            OnCollision = function(self)
                print("Collided with: " .. tostring(self:GetNumber("Collision","collider")))
            end
        }
    }
}
