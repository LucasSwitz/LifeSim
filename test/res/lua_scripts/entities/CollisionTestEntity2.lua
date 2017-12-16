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
            width = 32,
            height = 32,
            collision_script = Res("CharacterCollision.lua")
        }
    }
}
