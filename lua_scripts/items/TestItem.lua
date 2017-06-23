--PREAMBLE_START
ScriptType = "Entity"
Name = "TestItem"
--PREAMBLE_END

TestItem = 
{
    PrototypeID = 0,
    id = 1,
    Decorators = 
    {   
        Useable =
        {
            Use = function(self, user)
            {
                print("Being Used! :)")
            }
        },
        EventHandler = 
        {
            OnEvent(self, e) = function
            {
                if e.type = EventType.USE_EVENT then
                    self:Useable:Use()
            },
            GetSubscriptions = function(self)
            {
                return {LuaSubscription(EventType.USE_EVENT,{self.id})}
            }
        },
        Components = 
        {
            Graphics = 
            {

            }
        }
    }

}