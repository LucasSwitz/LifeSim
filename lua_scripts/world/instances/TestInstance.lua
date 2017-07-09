--PREAMBLE_START
ScriptType = "Instance"
Name = "TestInstance"
ID = 0
--PREAMBLE_END

TestInstance = 
{
    Load = function(test_instance)
        -- called once when the instance is first opened
        DebugFlags.Instance():Set("TestInstanceLoad","yes")
    end,
    Open = function(test_stage)
        -- called every time the instances comes into "scope"
        DebugFlags.Instance():Set("TestInstanceOpen","yes")
    end,
    Update = function(test_stage, seconds_elapsed)
        -- called every frame the instance is in "scope"
        DebugFlags.Instance():Set("TestInstanceUpdate","yes")
    end,
    Close = function(test_stage)
        -- called every time the instance leaves "scope"
        DebugFlags.Instance():Set("TestInstanceClose","yes")
    end,
    Unload = function(test_stage)
        -- called when the intstance will never be opened again
        DebugFlags.Instance():Set("TestInstanceUnload","yes")

    end,
    OnEvent = function(test_stage, event)
    
    end,
    GetSubscriptions = function(test_stage)
    
    end
}