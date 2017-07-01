--PREAMBLE_START
ScriptType = "Entity"
Name = "MoveableGraphicsTestEntity"
PrototypeID = 1114
--PREAMBLE_END

MoveableGraphicsTestEntity =
{
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
            x = 30 -- px/second
        }
    }
}