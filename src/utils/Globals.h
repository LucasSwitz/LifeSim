#ifndef GLOBALS_H
#define GLOBALS_H

#include "src/game/resources/ResourceManager.h"
#include <iostream>

#define Res(X) Globals::GetResource(X)

template <typename T>
using ptr = std::shared_ptr<T>;

struct AssetNotFoundException : public std::exception
{
  std::string _msg;
  AssetNotFoundException(const std::string &asset_name) : 
    _msg("Asset not found: " + asset_name) {}
  const char *what() const throw()
  {
    return _msg.c_str();
  }
};

struct FailedToLoadAssetException : public std::exception
{
  std::string _msg;
  FailedToLoadAssetException(const std::string &asset_name) : 
    _msg("Failed to load asset: " + asset_name) {}
  const char *what() const throw()
  {
    return _msg.c_str();
  }
};

template <typename T, typename TM>
static void expose_ptrs(const T &smart_pointers, TM &raw_pointers)
{
  for (auto sp : smart_pointers)
  {
    raw_pointers.push_back(sp.get());
  }
}

template <typename T, typename K>
static void expose_ptrs(const std::map<K, ptr<T>> smart_pointers, std::map<K, T *> raw_pointers)
{
  for (auto it = smart_pointers.begin(); it != smart_pointers.end(); it++)
  {
    raw_pointers.insert(std::make_pair(it->first, it->second.get()));
  }
}

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
    if (res)
    {
      return res->GetResource(resource_name);
    }
    else
    {
      std::cout << "No Resource Manager Loaded.";
      return "";
    }
  }
};

#endif
