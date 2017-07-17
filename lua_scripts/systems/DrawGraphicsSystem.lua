--PREAMBLE_START
ScriptType = "System"
Name = "DrawGraphicsSystem"
--PREAMBLE_END

DrawGraphicsSystem = 
{   
    Update = function(graphics_system,time)
        drawables = LuaListComponentUser()
        ComponentUsers.Instance():GetAll(drawables,{"Graphics","Position"})
        local it = drawables:Iterator()
        
        if it == nil then
            print("nil")
        end

        --Draw all objects with 'Graphics' component
        while it ~= nil do
            drawable = it.data
            e = Event.ComponentUserEvent(EventType.DRAW_REQUEST_EVENT,0,0,drawable)
            EventManager.Instance():LaunchEvent(e)
            it = it.next
        end
    end
}