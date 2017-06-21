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
        OnEvent = function(entity, event)
            --do something with the event
            if(event.type == EventType.COLLIDED_EVENT) then

                -- apply damage
                current_hp = entity:GetComponent("Health"):GetNumber("hp")
                damage = event.collider.damage
                LaunchEvent(EventType.HEALTH_CHANGE_EVENT, entity, current_hp - damage);
                -- apply knockback
                -- apply conditions

            else if event.type == EventType.HEALTH_CHANGE_EVENT then
                entity:GetComponent("Health"):SetNumber("hp", event.get("hp"))
            end
        end
        GetSubscriptions = function(entity, event)
            return {Subscription(EventType:HEALTH_CHANGE_EVENT, targets = {entity.ID}),
                    Subscription(EventType:COLLIDED_EVENT, targets = {entity.ID})} --something like this
        end
    }
}