--PREAMBLE_START
ScriptType = "Entity"
Name = "Fireball"
PrototypeID = 111
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
            sprite = "/home/pabu/Desktop/LifeSim/res/sprites/fireball.png",
            width = 100,
            height = 100,
            layer = 1
        },
        Mass = 
        {
            mass = 10
        },
        Collision = 
        {
            width = 24,
            height = 24,
            collision_script = "/home/pabu/Desktop/LifeSim/lua_scripts/collision/FireballCollision.lua",
        },
        Velocity =
        {
            x = 0,
            y = 0
        }
    }
}