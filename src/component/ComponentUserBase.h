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

typedef std::unordered_map<std::string, ptr<std::list<ComponentUser *>>> component_user_directoy;

typedef std::unordered_map<std::string, ptr<std::list<ComponentUserBaseSubscriber *>>>
    component_user_subscriber_directory;

typedef ptr<std::list<ComponentUser *>> component_user_list_ptr;
class ComponentUserBase : public ComponentUserListener
{
    friend class GameState;

  public:
    void DeRegister(std::string component_name, ComponentUser &user);
    void DeRegister(ComponentUser &user);
    bool ComponentExists(std::string component_name) const;

    void Reset()
    {
        _component_users_directory.clear();
    }

    const component_user_list_ptr GetAllUsersWithComponent(std::string component_name) const;
    component_user_list_ptr GetAllUsersWithComponentMutable(std::string component_name);
    void GetAllUsersWithComponents(std::initializer_list<std::string> list,
                                   std::list<ComponentUser *> &user_list);
    void GetAllUsersWithComponentsAsLuaList(LuaList<ComponentUser *> *lua_list, lua_State *L);
    void GetAllEntitesWithComponentAsLuaList(LuaList<Entity *> *lua_list, std::string component_name);
    void GetAllUsersWithComponents(std::list<std::string> &list, std::list<ComponentUser *> &matches);
    void GetAllUsersWithComponentAsLuaList(std::string &component_name, LuaList<ComponentUser *> &lua_list);

    void AddSubscriber(ComponentUserBaseSubscriber *sub, std::string comp_name);

    ptr<ComponentUser> GetComponentUser(int id);
    bool HasComponentUser(int id);
    void AddComponentUser(ptr<ComponentUser> user);
    void RemoveComponentUser(ptr<ComponentUser> user);
    void RemoveComponentUser(int id);
    int GetRegistrationCount(int id);
    bool IsRegistered(int id);

    //Inherited from ComponentUserListener
    void OnEnableComponent(ptr<ComponentUser> user, const std::string& component_name) override;
    void OnDisableComponent(ptr<ComponentUser> user, const std::string& component_name) override;

    ~ComponentUserBase(){};
    ComponentUserBase(){};

  private:
    void UpdateSubscribers(ComponentUserBaseEvent::Type _type, std::string component_name,
                           ComponentUser *user);

  private:
    void Register(std::string component_name, ptr<ComponentUser> user);

    component_user_directoy _component_users_directory;
    component_user_subscriber_directory _subscribers;
    std::map<int, ptr<ComponentUser>> _all_users;
    std::map<int, int> _registration_count;
    static ComponentUserBase *_instance;
};

#endif