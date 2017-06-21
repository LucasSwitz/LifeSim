--PREAMBLE_START
ScriptType = "Entity"
Name = "TestEntity"
PrototypeID = 999
--PREAMBLE_END

TestEntity = 
{
    ID = 999,
    Components = 
    {   
        Physics = 
        {
            mass = 10,
            max_velocity = 20
        },
        Graphics = 
        {
            still_frame = "test/file/path",
        },
        Animation
        {
            current_animation = "Idle",
            current_frame = "Still",
            current_frame_time_left = 0.0,
            next_frame = "None",
            started = false,
            is_finished = false,
            Animations = 
            {
                Walking = 
                {
                    Frames  =
                    {
                        Frame1 = 
                        {
                            duration = 2,
                            sprite_file = "path/to/sprite/file"
                        },
                        Frame2 = 
                        {
                            duration = 2,
                            sprite_file = "path/to/sprite/file"
                        }
                    }
                },
                Idle = 
                {
                    Frames = 
                    {
                        Still =
                        {
                            duration = -1,
                            sprite_file = "path/to/sprite/file"
                        }
                    }
                }
            }
        }
    },
    Subscriptions 
    {
        subscriptions = {"sub1","sub2"},
        OnEvent = function(entity, event)
            --do something with the event
            if(event.type == EventType.Collided) then

                -- apply damage
                damage = event.collider.damage
                current_hp = entity:GetComponent("Health"):GetNumber("hp")
                entity:GetComponent("Health"):SetNumber("hp", current_hp - damage)

                -- apply knockback
                -- apply conditions
            end
        end
    }
}