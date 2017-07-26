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
            collision_script = "/home/pabu/Desktop/LifeSim/lua_scripts/collision/GenericWallCollision.lua"
        },
        Mass = 
        {
            mass = 100
        },
        Graphics  = 
        {
            sprite = "/home/pabu/Desktop/LifeSim/res/textures/pumpkin.jpg",
            layer = 0
        }
    }
}