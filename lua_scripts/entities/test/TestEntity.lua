--PREAMBLE_START
ScriptType = "Entity"
Name = "TestEntity"
PrototypeID = 999
--PREAMBLE_END

TestEntity = 
{
    id = 999,
        Components = 
        {   
            Health = 
            {
                hp = 0
            },
            Position =
            {
                x_pos = 0,
                y_pos = 0
            },
            Velocity = 
            {
                x_velcoity = 0,
                y_velocity = 0,
                max_velocity = 0
            },
            Graphics = 
            {
                sprite = "still/sprite",
            },
            Collision = 
            {
                hit_box_width = 100,
                hit_box_height = 100,

                OnCollision = function(self, collider)
                    LaunchEvent(EventType.DAMAGE_EVENT, collider, self.damage) --good Make DamageSystem
                    LaunchEvent(EventType.ADD_CONDITION_EVENT, collider, self.damage) --good Make ConditionSystem
                    LaunchEvent(EventType.DELETE_ENTITY, self.id, self.id, nil) -- Make EntitySystem
                end
            },
            Useable
            { 
                Use = function(self, user)

                end,
            },
            Animation =
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
    }
}