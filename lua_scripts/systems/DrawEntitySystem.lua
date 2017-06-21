--PREAMBLE_START
ScriptType = "System"
Name = "DrawEntitySystem"
--PREAMBLE_END

DrawEntitySystem = 
{   
    after = "DrawUISystem",
    Update = function(graphics_system,time)
        local entities = EntityManager.Instance():AsLuaList()
        local it = entities:Iterator()
        local gui = Gui.Instance()
        
        --Draw All Entities
        while it ~= nil do
            entity = it.data
            gui:Draw(entity)
        end
        Gui.Instance():Update()
    end
}