


SpawningEntitySystem = 
{
    EventHandler = 
    {
        OnEvent = function(e)
            EntityManager:Instance()->Register(e)
        end
    }
}