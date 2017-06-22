#ifndef COMPONENTUSERBASE_H
#define COMPONENTUSERBASE_H

#include <unordered_map>
#include <list>
#include "src/utils/lua/LuaList.h"

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

std::list<ComponentUser*>* GetAllUsersWithComponent(std::string component_name);
LuaList<ComponentUser*>* GetAllUsersWithComponentAsLuaList(std::string component_name);


private:
    ComponentUserBase(){};

private:
    std::unordered_map<std::string, std::list<ComponentUser*>*> _component_users_directory;

};

#endif