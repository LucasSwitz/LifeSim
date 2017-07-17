--PREAMBLE_START
ScriptType = "System"
Name = "DrawGraphicsSystem"
--PREAMBLE_END

DrawGraphicsSystem = 
{   
    Update = function(graphics_system,time)
        local drawables = LuaListComponentUser()
        ComponentUsers.Instance():GetAll(drawables,{"Graphics","Position"})
        local it = drawables:Iterator()
        --Draw all objects with 'Graphics' component
        while it ~= nil do
            local drawable = it.data
            --e = Event.ComponentUserEvent(EventType.DRAW_REQUEST_EVENT,0,0,drawable)
            --EventManager.Instance():LaunchEvent(e)
            it = it.next
        end
    end
}