#ifndef GLOBALS_H
#define GLOBALS_H

#include "src/game/resources/ResourceManager.h"
#include <iostream>

#define Res(X) Globals::GetResource(X)

class Globals
{
public:
  static std::string RESOURCE_ROOT;
  static ResourceManager *res;

  static void SetResourceRoot(std::string root)
  {
    RESOURCE_ROOT = root;
    res = new ResourceManager(RESOURCE_ROOT);
  }

  static std::string GetResource(std::string resource_name)
  {
    if (res){
      return res->GetResource(resource_name);
    }
    else{
      std::cout << "No Resource Manager Loaded.";
      return "";
    }
  }
};

#endif
