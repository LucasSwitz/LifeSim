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