--PREAMBLE_START
ScriptType = "System"
Name = "DrawGraphicsSystem"
--PREAMBLE_END

DrawGraphicsSystem = 
{   
    Update = function(graphics_system,time)
        local drawables = ComponentUsers.Instance():GetAll({"Graphics","Position"})
        local it = drawables:Iterator()
        
        --Draw all objects with 'Graphics' component
        while it ~= nil do
            drawable = it.data
            EventManager.Instance():LaunchEvent(Event(EventType.DRAW_REQUEST_EVENT,0,0,drawable))
            it = it.next
        end
    end
}