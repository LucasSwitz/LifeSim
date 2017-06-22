#ifndef LAUDECORATED_H
#define LAUDECORATED_H

#include "src/decorator/Decorated.h"
#include "src/decorator/LuaEventHandlingDecorator.h"
#include "src/decorator/LuaComponentsDecorator.h"


class LuaDecorated : public Decorated
{
    public:
        void LoadLuaDecorators(const LuaRef& parent_table, const LuaRef& decoration_table)
        {
            if(decoration_table["Components"])
            {
                ComponentsDecorator* components = 
                    LuaComponentsDecorator::FromLuaRef(decoration_table["Components"]);
                AddComponents(components);
                
            }

            if(decoration_table["EventHandler"])
            {
                EventHandlingDecorator* event_handler = 
                    LuaEventHandlingDecorator::FromLuaRef(parent_table,decoration_table["EventHandler"]);
                AddEventHandling(event_handler);
            }
        }
};

#endif