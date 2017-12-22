--PREAMBLE_START
ScriptType = "UIWidget"
Name = "HealthWidget"
--PREAMBLE_END

--need cpp to understand UIWidget types

HealthWidget = 
{   
    Components
    {
        Graphics
        {
            sprite_path = "path/to/heart_image"
        },
        State = 
        {
            state = Res("HealthWidgetAliveState.lua"),
            stage = "Start",
            time = 0
        }
    }

    end
}
