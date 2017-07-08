--PREAMBLE_START
ScriptType = "Instance"
Name = "TestInstance"
--PREAMBLE_END

TestInstance = 
{
    tilemap = "",
    Load = function(test_instance, seconds_elapsed)
        -- called once when the instance is first opened

    end,
    Open = function(test_stage, seconds_elapsed)
        -- called every time the instances comes into "scope"

    end,
    Update = function(test_stage, seconds_elapsed)
        -- called every frame the instance is in "scope"

    end,
    Close = function(test_stage, seconds_elapsed)
        -- called every time the instance leaves "scope"
    end,
    Unload = function(test_stage, seconds_elapsed)
        -- called when the intstance will never be opened again

    end,
    OnEvent = function(test_stage, event)
    
    end,
    GetSubscriptions = function(test_stage)
    
    end
}