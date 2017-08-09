--PREAMBLE_START
ScriptType = "Entity"
Name = "Fireball"
PrototypeID = 111
--PREAMBLE_END

Fireball = 
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
            sprite = Res("fireball.png"),
            width = 10,
            height = 10,
            layer = 1
        },
        Mass = 
        {
            mass = .001
        },
        Collision = 
        {
            width = 10,
            height = 10,
            collision_script = Res("FireballCollision.lua"),
        },
        Velocity =
        {
            x = 0,
            y = 0
        },
        Acceleration = 
        {
            force_x = 0,
            force_y = 0,
            x = 0,
            y= 0
        }
    }
}