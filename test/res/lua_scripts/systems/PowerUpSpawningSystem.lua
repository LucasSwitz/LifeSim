--PREAMBLE_START
ScriptType = "System"
Name = "PowerUpSystem"
--PREAMBLE_END

POWER_UP_MAX_SPAWN_INTERVAL = 15
math.randomseed(os.time())

PowerUpSystem = 
{
    time_since_last_spawn  = 0.0,
    Update = function(state_system, time, g)
        state_system.time_since_last_spawn = state_system.time_since_last_spawn - (time + math.random(0,.5))
        if(state_system.time_since_last_spawn <= 0) then
            instance = GET_ACTIVE_INSTANCE()
            SpawnPowerUp(instance.x, instance.x + width, instance.y, instance.y + height) --need to pass width and height of current instance
            state_system.time_since_last_spawn = POWER_UP_MAX_SPAWN_INTERVAL
        end
    end,
    SpawnPowerUp = function(x_low, x_high, y_low, y_high)
        x = math.random(x_low,x_high)
        y = math.random(y_low, y_high)

        e = Event(EventType.SPAWN_ENTITY_EVENT_PROTOTYPE,FIREBALL_ENTITY_ID,GET_CURRENT_INTANCE().id)
        MessageDispatch.Instance():LaunchEvent(e)
        power_up = EntityManager.Instance:Last()
        power_up:SetNumber("Position","x",x)
        power_up:SetNumber("Position","y",y)
    end
}