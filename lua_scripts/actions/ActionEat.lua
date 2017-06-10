ActionEat = {
    SetPerformer=function(performer) 
        
        _performer = performer 
    end,
    Start=function()  print(_performer) end,
    Perform=function() 
        print("end") 
    end,
    IsFinished=function() 
        print("lol") 
    end
}
