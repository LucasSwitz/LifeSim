--PREAMBLE_START
ScriptType = "Entity"
Name = "CollisionTestEntity1"
PrototypeID = 1002
--PREAMBLE_END

CollisionTestEntity1 = 
{
    Components = 
    {
        Position =
        {
            x = 10,
            y = 10
        },
        Collision = 
        {
            width = 10,
            height = 10,
            OnCollision = function(self, collider)


            end
        }
    }
}
