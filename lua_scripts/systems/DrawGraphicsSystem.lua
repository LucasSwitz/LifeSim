--PREAMBLE_START
ScriptType = "System"
Name = "DrawGraphicsSystem"
--PREAMBLE_END

DrawGraphicsSystem = 
{   
    after = "ForwardAnimationSystem",
    Update = function(graphics_system,time)
        local drawables = ComponentUsersBase.Intance():GetAll("Graphics")
        local it = entities:Iterator()
        local gui = Gui.Instance()
        
        --Draw all objects with 'Graphics' component
        while it ~= nil do
            drawable = it.data
            gui:Draw(drawable)
        end
        Gui.Instance():Update()
    end
}