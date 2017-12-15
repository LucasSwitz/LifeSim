#ifndef COMPONENTUSERBASE_H
#define COMPONENTUSERBASE_H

#include <unordered_map>
#include <list>
#include <initializer_list>
#include <iostream>
#include "src/utils/lua/LuaList.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/game_objects/Entity.h"
#include "src/component/ComponentUserBaseEvent.h"
#include "src/component/ComponentUserBaseSubscriber.h"
#include "src/component/ComponentUserListener.h"

/**
    ComponentUserBase stores all component users and indexes them by the components they own.
    The Singleton instance of this class can be queried the get all ComponentUsers who have a specific
    component. 
**/
class ComponentUser;

class ComponentUserBase : public ComponentUserListener
{
    friend class GameState;

  public:
    void Register(std::string component_name, ComponentUser &user);
    void DeRegister(std::string component_name, ComponentUser &user);
    bool ComponentExists(std::string component_name) const;

    void Reset()
    {
        _component_users_directory.clear();
    }

    const std::list<ComponentUser*> *GetAllUsersWithComponent(std::string component_name) const;
    std::list<ComponentUser *> *GetAllUsersWithComponentMutable(std::string component_name);
    void GetAllUsersWithComponents(std::initializer_list<std::string> list,
                                   std::list<ComponentUser *> &user_list);
    void GetAllUsersWithComponentsAsLuaList(LuaList<ComponentUser *>* lua_list, lua_State *L);
    void GetAllEntitesWithComponentAsLuaList(LuaList<Entity *> *lua_list, std::string component_name); 
    void GetAllUsersWithComponents(std::list<std::string> &list, std::list<ComponentUser *> &matches);
    void GetAllUsersWithComponentAsLuaList(std::string &component_name, LuaList<ComponentUser *> &lua_list);

    void AddSubscriber(ComponentUserBaseSubscriber* sub, std::string comp_name);

    ComponentUser* GetComponentUser(int id);
    bool HasComponentUser(int id);
    void AddComponentUser(ComponentUser* user);
    void RemoveComponentUser(ComponentUser* user);
    int GetRegistrationCount(int id);
    bool IsRegistered(int id);
    
    //Inherited from ComponentUserListener
    void OnEnableComponent(ComponentUser* user, const std::string component_name);
    void OnDisableComponent(ComponentUser* user, const std::string component_name);
    
    ~ComponentUserBase(){};
    ComponentUserBase(){};

  private:
    void UpdateSubscribers(ComponentUserBaseEvent::Type _type, std::string component_name,
        ComponentUser* user);

  private:
    std::unordered_map<std::string, std::list<ComponentUser *> *> _component_users_directory;
    std::unordered_map<std::string, std::list<ComponentUserBaseSubscriber*>* > _subscribers;
    std::map<int,ComponentUser*> _all_users;
    std::map<int, int> _registration_count;
    static ComponentUserBase *_instance;
};

#endif