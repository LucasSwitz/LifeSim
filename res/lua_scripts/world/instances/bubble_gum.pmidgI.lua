--PREAMBLE_START 
ScriptType = "Instance" 
Name = "bubble_gum" 
ID = 1971922240
--PREAMBLE_END

bubble_gum = 
 { 
tile_map = "/home/pabu/Desktop/LifeSim/res/tile_maps/bubble_gum.pmidgM", 
Load = function(instance)
end, 
Open = function(instance)
	e = Event.StringsEvent(EventType.START_SYSTEM_EVENT,-1,-1,{"AnimationSystem"})
    MessageDispatch.Instance():LaunchEvent(e)
end, 
Update = function(instance,seconds_elapsed)
	
end, 
Close = function(instance)
    e = Event.StringsEvent(EventType.STOP_SYSTEM_EVENT,-1,-1,{"AnimationSystem"})
    MessageDispatch.Instance():LaunchEvent(e)
end, 
Unload = function(instance)
	
end, 
OnEvent = function(instance,event)
	
end, 
GetSubscriptions = function(instance)
	
end, 
}