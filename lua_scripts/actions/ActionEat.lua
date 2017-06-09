require "actions.Action"

ActionEat = Action:new()

function ActionEat:new(performer)
    new_instance = Action:new(performer)
    setmetatable(new_instance,self)
    self.__index = self
    return new_instance
end

function ActionEat:Start()
    print(self.performer)
end
