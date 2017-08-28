--PREAMBLE_START
ScriptType = "System"
Name = "AnimationSystem"
--PREAMBLE_END

AnimationSystem = 
{   
    Update = function(graphics_system,time, g)
        local animated = LuaListComponentUser()
        ComponentUsers.Instance():GetAll(animated,{"Animation","Graphics"})
        local it = animated:Iterator()

        --Forward All Animations
        while it ~= nil do 
            entity = it.data

            animation_component = entity:GetComponent("Animation")
            animation_started = animation_component:GetBool("started")
            
            if not animation_started then
                graphics_system:StartAnimation(animation_component, entity)
            end

            --Decrease time left on frame
            current_frame_time_left = animation_component:GetNumber("current_frame_time_left")
            current_frame_time_left = current_frame_time_left - time
            animation_component:SetNumber("current_frame_time_left",current_frame_time_left)
            if current_frame_time_left <= 0 then
                graphics_system:ForwardAnimation(animation_component, entity)
            end
            it = it.next     
        end
    end,
    StartAnimation = function(graphics_system, animation_component, graphic_user)
        animation_name = animation_component:GetString("animation")
        animation = animation_component:GetSubcomponent("Animations"):GetSubcomponent(animation_name)
        start_frame_name = animation:GetString("start_frame")

        graphics_system:StartFrame(animation,start_frame_name,animation_component, graphic_user)

        animation_component:SetBool("started",true)     
    end,
    ForwardAnimation = function(graphics_system, animation_component, graphic_user)
        current_animation_name = animation_component:GetString("animation")
        next_frame_name = animation_component:GetString("next_frame")

        animation = animation_component:GetSubcomponent("Animations"):GetSubcomponent(current_animation_name)

        graphics_system:StartFrame(animation, next_frame_name, animation_component, graphic_user)
    end,
    StartFrame = function (graphics_system, animation, frame_name, animation_component, graphic_user)
        frame = animation:GetSubcomponent("Frames"):GetSubcomponent(frame_name)

        frame_sprite = frame:GetString("sprite")
        frame_duration = frame:GetNumber("duration")
        next_frame_name = frame:GetString("next")

        animation_component:SetString("current_frame", frame_name)
        animation_component:SetNumber("current_frame_time_left", frame_duration)
        animation_component:SetString("next_frame", next_frame_name)
        graphic_user:SetString("Graphics","sprite",frame_sprite)
    end
}