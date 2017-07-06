--PREAMBLE_START
ScriptType = "Stage"
Name = "TestStage"
--PREAMBLE_END

TestStage = 
{
    Start = function(test_stage, seconds_elapsed)
        -- spawn characters
        -- maybe cutscene
        -- load nessesary systems

    end,
    Update = function(test_stage, seconds_elapsed)
        -- timed events?

    end,
    End = function(test_stage, seconds_elapsed)
      -- Remove systems maybe?

    end,
    OnEvent = function(test_stage, event)
    
    end
}