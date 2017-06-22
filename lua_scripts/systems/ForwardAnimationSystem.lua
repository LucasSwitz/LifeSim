--PREAMBLE_START
ScriptType = "SystemBLCK"
Name = "ForwardAnimationSystem"
--PREAMBLE_END

ForwardAnimationSystem = 
{   
    after = "HealthSystem",
    Update = function(graphics_system,time)
        local animated = ComponentUserBase.Instance():GetAll("Animation")
        local it = animated:Iterator()

        --Forward All Animations
        while it ~- nil do 
            entity = it.data,
            animation_component = entity:GetComponent("Animation")

            frame_started = animation_component:GetBool("started")

            --Check if frame has started
            if !frame_started then
                animation_component:SetBool("started",true)
                --Set entity sprite to new frame
                entity:GetComponent:("Graphics"):SetString("sprite",animation_component:GetString("current_frame_sprite")) --should this be an event?
            else
            --Decrease time left on frame
            current_frame_time_left = animation_component:GetNumber("current_frame_time_left")
            current_frame_time_left = current_frame_time_left - time

            if current_frame_time_left < 0:
                ForwardAnimation(animation_component)
            end     
        end
    end,

    ForwardAnimation = function(animation_component)
        current_animation_name = animation_component:GetString("current_anmiation_name")
        next_frame_name = animation_component:GetString("next_frame")
        next_frame = animation_component:GetSubcomponent("Animations")
                                                 :GetSubcomponent(current_animation_name)
                                                 :GetSubcomponent("Frames")
                                                 :GetSubcomponent(next_frame_name)
        next_frame_duration = next_frame:GetNumber("duration")
        next_next_frame_name = next_frame:GetString("next_frame_name")

        animation_component:SetString("current_frame", next_frame_name)
        animation_component:SetBool("started", false)
        animation_component:SetNumber("current_frame_time_left", next_frame_duration)
        animation_component:SetString("next_frame", next_next_frame_name)
    end
}