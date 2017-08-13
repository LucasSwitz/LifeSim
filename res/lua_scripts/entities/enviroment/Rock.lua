--PREAMBLE_START
ScriptType = "Entity"
Name = "Rock"
PrototypeID = 888
--PREAMBLE_END

Rock = 
{
    Components = 
    {
        Position = 
        {
            x = 0,
            y = 0
        },
        Graphics = 
        {
            sprite = Res("rock.png"),
            width = 128,
            height = 128,
            layer = 1
        },
        Mass = 
        {
            mass = 10000
        },
        Collision = 
        {
            width = 64,
            height = 64,
            collision_script = Res("ZeroRestitutionWallCollision.lua"),
        },
        Velocity =
        {
            x = 0,
            y = 0
        }
    }
}