--PREAMBLE_START
ScriptType = "Tile"
Name = "TestTile2"
ID = 1
--PREAMBLE_END

TestTile2 = 
{
    Components = 
    {
        Position =
        {
            x = 0,
            y = 0
        },
        Graphics  = 
        {
            sprite = "/home/lucas/Desktop/LifeSim/res/textures/diamonds.jpg",
            layer = 0
        },
        Collision = 
        {
            width = 32,
            height = 32,
            collision_script = "/home/lucas/Desktop/LifeSim/lua_scripts/collision/ZeroRestitutionWallCollision.lua"
        },
    }
}