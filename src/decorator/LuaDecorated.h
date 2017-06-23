#ifndef LAUDECORATED_H
#define LAUDECORATED_H

#include "src/decorator/Decorated.h"
#include "src/decorator/LuaEventHandlingDecorator.h"
#include "src/decorator/LuaComponentsDecorator.h"

class LuaDecorated : public Decorated
{
    public:
        void LoadLuaDecorators(const LuaRef& parent_table)
        {
            if(parent_table["Decorators"])
            {
                LuaRef decoration_table = parent_table["Decorators"];
                if(decoration_table["Components"])
                {
                    ComponentsDecorator* components_decorator = 
                        LuaComponentsDecorator::FromLuaRef(decoration_table["Components"]);
                    AddComponents(components_decorator);   
                }

                if(decoration_table["EventHandler"])
                {
                    EventHandlingDecorator* event_handler = 
                        LuaEventHandlingDecorator::FromLuaRef(parent_table,decoration_table["EventHandler"]);
                    AddEventHandling(event_handler);
                }
            }
        }
};

#endif