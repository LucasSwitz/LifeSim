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

    Linked_Components
    {
        Player_1_Health
        {
            component_owner = 0,
            component_name = "Health"
        }
    }   
    Update = function(component_map)

    end
}
