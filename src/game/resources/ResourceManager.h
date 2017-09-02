#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#define Res(X) ResourceManager::GetResource(X)

#include "src/utils/system/FileCrawler.h"

class ResourceManager
{
  public:

    static std::string GetResource(std::string resource_name)
    {
        ResourceManager* instance = ResourceManager::Instance();
        if(instance->HasResource(resource_name))
            return instance->_resource_paths.at(resource_name);
        return "";
    }

    bool HasResource(std::string resource_name)
    {
        return _resource_paths.find(resource_name) != _resource_paths.end();
    }

    static ResourceManager* Instance()
    {
        static ResourceManager instance("/home/lucas/Desktop/LifeSim/res");
        return &instance;
    }

  private:
    ResourceManager(std::string resource_directory_path)
    {
        FileCrawler crawler;
        crawler.Crawl(resource_directory_path,_resource_paths);
    }

    std::unordered_map<std::string, std::string> _resource_paths;
};
#endif