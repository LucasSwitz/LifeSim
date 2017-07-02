--PREAMBLE_START
ScriptType = "System"
Name = "DrawGraphicsSystem"
--PREAMBLE_END

DrawGraphicsSystem = 
{   
    Update = function(graphics_system,time)
        local drawables = ComponentUsers.Instance():GetAll({"Graphics","Position"})
        local it = drawables:Iterator()
        local gui = GameWindow.Instance()
        
        --Draw all objects with 'Graphics' component
        while it ~= nil do
            drawable = it.data
            gui:Draw(drawable)
            it = it.next
        end
    end
}