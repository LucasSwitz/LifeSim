--PREAMBLE_START
ScriptType = "System"
Name = "FollowCharacterCamera"
--PREAMBLE_END

FollowCharacterCamera =
{
    Update = function(follower_camera,time,g)
        players = LuaListComponentUser()
        g:ComponentUsers():GetAll(players,{"Player","Position"})
        players_it = players:Iterator()
        player = players_it.data

        x = player:GetNumber("Position","x")
        y = player:GetNumber("Position","y")

        e = Event.FloatsEvent(EventType.RECENTER_VIEW_EVENT,-1,TARGET_WINDOW(),{x,y})
        EngineEventManager.Instance():LaunchEvent(e)
    end
}