


SpawningEntitySystem = 
{
    Decorators = 
    {
        EventHandler = 
        {
            OnEvent = function(e)
                EntityManager:Instance()->Register(e)
            end
        }
    }

}