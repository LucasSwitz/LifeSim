--PREAMBLE_START
ScriptType = "Entity"
Name = "TestEntity"
PrototypeID = 999
--PREAMBLE_END

TestEntity = 
{
    ID = 999,
    Components = 
    {   
        Physics = 
        {
            mass = 10,
            max_velocity = 20
        },
        Graphics = 
        {
            sprite_file = "test/file/path"
        }
    }
}