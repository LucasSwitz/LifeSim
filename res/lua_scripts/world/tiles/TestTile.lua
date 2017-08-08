--PREAMBLE_START
ScriptType = "Tile"
Name = "TestTile"
ID = 0
--PREAMBLE_END

TestTile = 
{
    Components = 
    {
        Position =
        {
            x = 0,
            y = 0
        },
        Collision = 
        {
            width = 32,
            height = 32,
            collision_script = Res("GenericWallCollision.lua")
        },
        Mass = 
        {
            mass = 100
        },
        Graphics  = 
        {
            sprite = Res("pumpkin.jpg"),
            layer = 0
        }
    }
}