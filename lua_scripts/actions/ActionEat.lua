--PREAMBLE_START
ScriptType = "Action"
Owner = "Actor"
Name = "ActionEat"
--PREAMBLE_END

ActionEat = {
    SetPerformer=function(performer) 
        
        _performer = performer 
    end,
    Start=function()  
        _performer:SetInternalValue("Hunger",5);
    end,
    Perform=function() 
    end,
    IsFinished=function() 
    end
}
