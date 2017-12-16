--PREAMBLE_START
ScriptType = "Stage"
Name = "TestStage"
ID = 0
--PREAMBLE_END

TestStage = 
{
    root = "TestInstance",
    Enter = function(test_stage, seconds_elapsed)
        -- load stage-specific systems
        DebugFlags.Instance():Set("TestStageEnter","yes")
    end,
    Update = function(test_stage, seconds_elapsed)
        DebugFlags.Instance():Set("TestStageUpdate","yes")     
    end,
    Exit = function(test_stage, seconds_elapsed)
      -- remove systems      
        DebugFlags.Instance():Set("TestStageExit","yes")     
    end,
    OnEvent = function(test_stage, event)
    
    end,
    GetSubscriptions = function(test_stage)
    
    end
}