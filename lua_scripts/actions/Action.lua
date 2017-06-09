
Action = {performer = ""}

function Action:new (performer)
    new_instance = {}
    setmetatable(new_instance,self)
    self.__index = self
    self.performer = performer or ""
    return new_instance
end

function Action:start()
    print("Override Me!")
end

function Action:finish()
    print("Override Me!")     
end

function Action:perform()
    print("Override Me!")
end
