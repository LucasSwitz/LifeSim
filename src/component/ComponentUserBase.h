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

    typedef std::unordered_map<std::string, ptr<std::list<ptr<ComponentUser>>>> component_user_directoy;
        

    typedef std::unordered_map<std::string, ptr<std::list<ComponentUserBaseSubscriber*>>> 
        component_user_subscriber_directory;

    typedef ptr<std::list<ptr<ComponentUser>>> component_user_list_ptr;

    void Register(std::string component_name, ComponentUser &user);
    void DeRegister(std::string component_name, ComponentUser &user);
    bool ComponentExists(std::string component_name) const;

    void Reset()
    {
        _component_users_directory.clear();
    }

    const component_user_list_ptr GetAllUsersWithComponent(std::string component_name) const;
    component_user_list_ptr GetAllUsersWithComponentMutable(std::string component_name);
    void GetAllUsersWithComponents(std::initializer_list<std::string> list,
                                   std::list<ptr<ComponentUser>> &user_list);
    void GetAllUsersWithComponentsAsLuaList(LuaList<ComponentUser *> *lua_list, lua_State *L);
    void GetAllEntitesWithComponentAsLuaList(LuaList<Entity *> *lua_list, std::string component_name);
    void GetAllUsersWithComponents(std::list<std::string> &list, std::list<ptr<ComponentUser>> &matches);
    void GetAllUsersWithComponentAsLuaList(std::string &component_name, LuaList<ComponentUser *> &lua_list);

    void AddSubscriber(ComponentUserBaseSubscriber* sub, std::string comp_name);

    ptr<ComponentUser> GetComponentUser(int id);
    bool HasComponentUser(int id);
    void AddComponentUser(ptr<ComponentUser> user);
    void RemoveComponentUser(ptr<ComponentUser> user);
    int GetRegistrationCount(int id);
    bool IsRegistered(int id);

    //Inherited from ComponentUserListener
    void OnEnableComponent(ComponentUser* user, const std::string component_name);
    void OnDisableComponent(ComponentUser* user, const std::string component_name);

    ~ComponentUserBase(){};
    ComponentUserBase(){};

  private:
    void UpdateSubscribers(ComponentUserBaseEvent::Type _type, std::string component_name,
                           ptr<ComponentUser> user);

  private:
    component_user_directoy _component_users_directory;
    component_user_subscriber_directory _subscribers;
    std::map<int, ptr<ComponentUser>> _all_users;
    std::map<int, int> _registration_count;
    static ComponentUserBase *_instance;
};

#endif