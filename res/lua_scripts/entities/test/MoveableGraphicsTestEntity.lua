--PREAMBLE_START
ScriptType = "Entity"
Name = "MoveableGraphicsTestEntity"
PrototypeID = 1114
--PREAMBLE_END

MoveableGraphicsTestEntity =
{
    id = 0,
    Components = 
    {
        Position = 
        {
            x = 90,
            y = 90
        },
        Graphics = 
        {
            sprite = "/home/pabu/Desktop/LifeSim/res/sprites/8_Bit_Mario.png"
        },
        Velocity =
        {
            x = 0, -- px/second
            y = 0
        },
        Acceleration = 
        {
            force_x = 0,
            force_y = 0,
            x = 0,
            y= 0
        },
        Mass = 
        {
            mass = 1
        }
    }
}