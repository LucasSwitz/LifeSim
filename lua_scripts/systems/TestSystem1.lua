--PREAMBLE_START
ScriptType = "System"
Name = "TestSystem1"
--PREAMBLE_END

TestSystem1 = 
{   
    total_time = 0.0,
    Update = function(system,time)
        system.total_time = system.total_time + time
        print(system.total_time)
    end
}