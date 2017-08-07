--PREAMBLE_START
ScriptType = "Entity"
Name = "AnimationTestEntity"
PrototypeID = 1800
--PREAMBLE_END

AnimationTestEntity = 
{
        Components = 
        {   
            Graphics = 
            {
                sprite = "sprite",
            },
            Animation =
            {
                curent_frame_sprite = "/home/lucas/Desktop/LifeSim/res/sprites/8_Bit_Mario.png",
                current_animation = "Idle",
                current_frame = "Still",
                current_frame_time_left = 0.0,
                next_frame = "Still",
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
                                sprite_file = "/home/lucas/Desktop/LifeSim/res/sprites/8_Bit_Mario.png",
                                next_frame_name = "Frame2"
                            },
                            Frame2 = 
                            {
                                duration = 2,
                                sprite_file = "/home/lucas/Desktop/LifeSim/res/sprites/mario_jump.png",
                                next_frame_name = "Frame1"
                            }
                        }
                    },
                    Idle = 
                    {
                        Frames = 
                        {
                            Still =
                            {
                                duration = 0,
                                sprite_file = "/home/lucas/Desktop/LifeSim/res/sprites/8_Bit_Mario.png",
                                next_frame = "Still"
                            }
                        }
                    }
                }
            }
    }
}