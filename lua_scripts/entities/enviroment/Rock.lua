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
            sprite = "/home/pabu/Desktop/LifeSim/res/sprites/rock.png",
            width = 100,
            height = 100
        },
        Mass = 
        {
            mass = 10000
        },
        Collision = 
        {
            width = 24,
            height = 24,
            collision_script = "/home/pabu/Desktop/LifeSim/lua_scripts/collision/GenericWallCollision.lua",
        }
    }
}