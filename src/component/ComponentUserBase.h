#ifndef COMPONENTUSERBASE_H
#define COMPONENTUSERBASE_H

#include <unordered_map>
#include <list>
#include <initializer_list>
#include "src/utils/lua/LuaList.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/game_objects/Entity.h"
#include <iostream>

/**
    ComponentUserBase stores all component users and indexes them by the components they own.
    The Singleton instance of this class can be queried the get all ComponentUsers who have a specific
    component.
**/
class ComponentUser;

class ComponentUserBase
{

public:

static ComponentUserBase* Instance()
{
    static ComponentUserBase instance;
    return &instance;
}

void Register(std::string component_name,ComponentUser& user);
void DeRegister(std::string component_name,ComponentUser& user);
bool ComponentExists(std::string component_name);

void Reset()
{
    _component_users_directory.clear();
}

std::list<ComponentUser*>* GetAllUsersWithComponent(std::string component_name);
void GetAllUsersWithComponents(std::initializer_list<std::string> list,
                                    std::list<ComponentUser*>& user_list);
void GetAllUsersWithComponentsAsLuaList(LuaList<ComponentUser*>* lua_list, lua_State* L);
void GetAllEntitesWithComponentAsLuaList(std::string component_name, LuaList<Entity*>& lua_list);
void GetAllUsersWithComponents(std::list<std::string>& list, std::list<ComponentUser*>& matches);
void GetAllUsersWithComponentAsLuaList(std::string& component_name, LuaList<ComponentUser*>& lua_list);

private:
    ComponentUserBase(){};

private:
    std::unordered_map<std::string, std::list<ComponentUser*>*> _component_users_directory;

};

#endif