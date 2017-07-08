--PREAMBLE_START
ScriptType = "Stage"
Name = "TestStage"
--PREAMBLE_END

TestStage = 
{
    root = "TestInstance",
    Start = function(test_stage, seconds_elapsed)
        -- load stage-specific systems
    
    end,
    Update = function(test_stage, seconds_elapsed)
     
    end,
    End = function(test_stage, seconds_elapsed)
      -- remove systems

    end,
    OnEvent = function(test_stage, event)
    
    end,
    GetSubscriptions = function(test_stage)
    
    end
}