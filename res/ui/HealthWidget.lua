--PREAMBLE_START
ScriptType = "UIElement"
Name = "HealthWidget"
--PREAMBLE_END

HealthWidget = 
{   
    Components =
    {
        Graphics =
        {
            sprite = Res("mario_1.png")
        },
        State = 
        {
            state = Res("HealthWidgetAliveState.lua"),
            stage = "Start",
            time = 0
        }
    }
}
