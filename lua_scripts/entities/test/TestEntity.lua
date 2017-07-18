--PREAMBLE_START
ScriptType = "Entity"
Name = "TestEntity"
PrototypeID = 1000
--PREAMBLE_END

TestEntity = 
{
        id = 0,
        Components = 
        {

            Position = 
            {
                x = 90,
                y = 90
            },
            Graphics = 
            {
                sprite = "/home/pabu/Desktop/LifeSim/res/sprites/8_Bit_Mario.png"
            },
            Velocity =
            {
                x = 0, -- px/second
                y = 0,
                max = 100,
                heading = 0
            },
            Acceleration = 
            {
                force_x = 0,
                force_y = 0,
                x = 0,
                y= 0
            },
            Mass = 
            {
                mass = 1
            },
            Collision = 
            {
                width = 32,
                height = 32,
                collision_script = ""
            },
            State = 
            {
                state = "/home/pabu/Desktop/LifeSim/lua_scripts/states/character_state/CharacterIdleState.lua",
                stage = "Start"
            },
            Animation =
            {
                animation = "Idle",
                current_frame = "Still",
                current_frame_time_left = 0.0,
                next_frame = "Still",
                started = false,
                is_finished = false,
                Animations = 
                {
                    Walking = 
                    {
                        start_frame = "Frame1",
                        Frames  =
                        {
                            Frame1 = 
                            {
                                duration = 0.1,
                                sprite= "/home/pabu/Desktop/LifeSim/res/sprites/mario_1.png",
                                next = "Frame2"
                            },
                            Frame2 = 
                            {
                                duration = 0.1,
                                sprite = "/home/pabu/Desktop/LifeSim/res/sprites/mario_2.png",
                                next = "Frame3"
                            },
                            Frame3 = 
                            {
                                duration = 0.1,
                                sprite= "/home/pabu/Desktop/LifeSim/res/sprites/mario_3.png",
                                next = "Frame4"
                            },
                            Frame4 = 
                            {
                                duration = 0.1,
                                sprite = "/home/pabu/Desktop/LifeSim/res/sprites/mario_4.png",
                                next = "Frame1"
                            }
                        }
                    },
                    Idle = 
                    {
                        start_frame = "Still",
                        Frames = 
                        {
                            Still =
                            {
                                duration = 0,
                                sprite = "/home/pabu/Desktop/LifeSim/res/sprites/mario_1.png",
                                next = "Still"
                            }
                        }
                    }
                }
            }
    }
}