--PREAMBLE_START 
ScriptType = "Instance" 
Name = "TestInstance" 
ID = 919
--PREAMBLE_END

TestInstance = 
 { 
tile_map = "/home/lucas/Desktop/LifeSim/res/tile_maps/arena.pmidgM", 
Load = function(instance)
	DebugFlags.Instance():Set("TestInstanceLoad","yes")
end, 
Open = function(instance)
    DebugFlags.Instance():Set("TestInstanceOpen","yes")    
end, 
Update = function(instance,seconds_elapsed)
     DebugFlags.Instance():Set("TestInstanceUpdate","yes")    
end, 
Close = function(instance)
     DebugFlags.Instance():Set("TestInstanceClose","yes")    
end, 
Unload = function(instance)
     DebugFlags.Instance():Set("TestInstanceUnload","yes")
end, 
OnEvent = function(instance,event)
     DebugFlags.Instance():Set("TestInstanceOnEvent","yes")
end, 
GetSubscriptions = function(instance)
     DebugFlags.Instance():Set("TestInstanceGetSubscriptions","yes") 
end 
}