#include <LuaBridge/LuaBridge.h>
#include "src/game_objects/actor/Actor.h"

using namespace luabridge;

class LuaBindings
    {
    public:
        static void Bind(lua_State *L)
        { 
            getGlobalNamespace(L)
            .beginClass<Entity>("Entity")
            .endClass()
            .deriveClass<Actor, Entity>("Actor")
                .addConstructor<void(*)(void)>()
                .addFunction("SetInternalValue", &Actor::SetInternalValue)
                .addFunction("GetInternalValue", &Actor::GetInternalValue)
            .endClass();
        } 
 };