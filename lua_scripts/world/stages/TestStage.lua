--PREAMBLE_START
ScriptType = "Stage"
Name = "TestStage"
--PREAMBLE_END

TestStage = 
{
    root = "TestInstance",
    Start = function(test_stage, seconds_elapsed)
        -- load stage-specific systems
        DebugFlags.Instance():Set("TestStageStart","yes")
    end,
    Update = function(test_stage, seconds_elapsed)
        DebugFlags.Instance():Set("TestStageUpdate","yes")     
    end,
    End = function(test_stage, seconds_elapsed)
      -- remove systems      
        DebugFlags.Instance():Set("TestStageEnd","yes")     
    end,
    OnEvent = function(test_stage, event)
    
    end,
    GetSubscriptions = function(test_stage)
    
    end
}