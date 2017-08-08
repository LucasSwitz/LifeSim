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
        }
    },
    Subscriptions
    {
        subscriptions = {"Player1Health"}
        onEvent(widget, event)
        {
            --change number of hearts
        }
    }

    end
}
