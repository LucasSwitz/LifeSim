--PREAMBLE_START
ScriptType = "System"
Name = "GraphicsSystem"
--PREAMBLE_END

GraphicsSystem = 
{   
    after = "HealthSystem",
    Update = function(graphics_system,time)
        local entities = EntityManager.Instance():AsLuaList()
        local it = entities:Iterator()
        local gui = Gui.Instance();

        --Draw All Entities
        while it ~= nil do
            entity = it.data
            gui:Draw(entity)
        end

        --Draw UI Components
        gui:Draw(UIOverlay:AsDrawable())

        Gui.Instance():Update()
    end
}