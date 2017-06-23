--PREAMBLE_START
ScriptType = "ItemAction"
BindTo = "TestItem"
Name = "TestItemAction"
ID = 100
--PREAMBLE_END

SPAWNABLE_ID = 0
SPAWNABLE_SOUND = 2

TestItemAction =
{
    time_left = 0.0,
    Start = function(self,user)
        --remove player input
        LaunchEvent(EventType.ACTION_START_EVENT,0,0,self)
    end,
    Do = function(self,user)
        test_spawnable = PrototypeFactorty.Get(SPAWNABLE_ID)

        test_spawnable:SetComponentValueNumber("Physics","velocity",10)
        LaunchEvent(EventType.SPAWN_ENTITY_EVENT,0,0,test_spawnable)
        LaunchEvent(EventType.PLAY_SOUND_EVENT,0,0,SPAWNABLE_SOUND)
    end,
    End = function(self,user)
        LaunchEvent(EventType.ACTION_END_EVENT,0,0,self)
    end
}