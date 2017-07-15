--PREAMBLE_START
ScriptType = "System"
Name = "RegenerationSystem"
--PREAMBLE_END

HEALTH_REGEN_PERIOD = 3 --seconds

RegenerationSystem = 
{
    total_time = 0.0,

    Update = function(self,time)
        self.total_time = self.total_time + time
        if self.total_time >= HEALTH_REGEN_PERIOD then
            self.total_time = 0
            self:RegenerateAll()
        end
    end,
    RegenerateAll = function()
        local entities = ComponentUsers.Instance():GetAll({"Health"})
        local it = entities:Iterator()
        while it ~= nil do
            entity = it.data
            current_hp = entity:GetNumber("Health", "hp")
            entity:SetNumber("Health", "hp", current_hp + 10)
            --LaunchEvent(Event(EventType.HEALTH_CHANGE_EVENT, nil, entity.id, current_hp + 10))
            it = it.next
        end
    end,
}