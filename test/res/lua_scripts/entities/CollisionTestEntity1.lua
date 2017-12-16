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
            width = 32,
            height = 32,
            collision_script = Res("CharacterCollision.lua")
        }
    }
}
