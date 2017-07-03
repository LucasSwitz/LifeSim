--PREAMBLE_START
ScriptType = "Entity"
Name = "TestEntity"
PrototypeID = 1000
--PREAMBLE_END

TestEntity = 
{
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
                sprite = "sprite",
            },
            Collision = 
            {
                hit_box_width = 100,
                hit_box_height = 100,
            },
            State = 
            {
                state = "/home/pabu/Desktop/LifeSim/lua_scripts/states/character_state/CharacterIdleState.lua",
                stage = 0
            }
            Animation =
            {
                curent_frame_sprite = "path/to/sprite/file"
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
                                sprite_file = "/home/pabu/Desktop/LifeSim/res/sprites/8_Bit_Mario.png"
                                next_frame_name = "Frame2"
                            },
                            Frame2 = 
                            {
                                duration = 2,
                                sprite_file = "/home/pabu/Desktop/LifeSim/res/sprites/mario_jump.png"
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
                                sprite_file = "path/to/sprite/file"
                                next_frame = "Still"
                            }
                        }
                    }
                }
            }
    }
}