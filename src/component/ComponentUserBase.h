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
    friend class GameState;

  public:
    static ComponentUserBase *Instance()
    {
        return _instance;
    }

    static void GiveOwnership(ComponentUserBase *instance)
    {
        _instance = instance;
    }

    void Register(std::string component_name, ComponentUser &user);
    void DeRegister(std::string component_name, ComponentUser &user);
    bool ComponentExists(std::string component_name);

    void Reset()
    {
        _component_users_directory.clear();
    }

    std::list<ComponentUser *> *GetAllUsersWithComponent(std::string component_name);
    void GetAllUsersWithComponents(std::initializer_list<std::string> list,
                                   std::list<ComponentUser *> &user_list);
    void GetAllUsersWithComponentsAsLuaList(LuaList<ComponentUser *> *lua_list, lua_State *L);
    void GetAllEntitesWithComponentAsLuaList(std::string component_name, LuaList<Entity *> *lua_list);
    void GetAllUsersWithComponents(std::list<std::string> &list, std::list<ComponentUser *> &matches);
    void GetAllUsersWithComponentAsLuaList(std::string &component_name, LuaList<ComponentUser *> &lua_list);

    ~ComponentUserBase()
    {
        /*for (auto it = _component_users_directory.begin(); it != _component_users_directory.end();)
        {
            std::list<ComponentUser *> *list_to_delete = it->second;

            for (auto it_list = list_to_delete->begin(); it_list != list_to_delete->end();)
            {
                ComponentUser *user_to_delete = *it_list;

                it_list = list_to_delete->erase(it_list);

                delete user_to_delete;
            }

            delete list_to_delete;

            it = _component_users_directory.erase(it);
        }*/

        _instance = nullptr;
    }

  private:
    ComponentUserBase(){};

  private:
    std::unordered_map<std::string, std::list<ComponentUser *> *> _component_users_directory;
    static ComponentUserBase *_instance;
};

#endif