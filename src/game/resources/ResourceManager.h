#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "src/utils/system/FileCrawler.h"
#include <unordered_map>
#include <iostream>
class ResourceManager
{
  public:

    std::string GetResource(std::string resource_name)
    {
        if(HasResource(resource_name))
            return _resource_paths.at(resource_name);
        return "";
    }

    bool HasResource(std::string resource_name)
    {
        return _resource_paths.find(resource_name) != _resource_paths.end();
    }

    ResourceManager(std::string resource_directory_path)
    {
        FileCrawler crawler;
        crawler.Crawl(resource_directory_path,_resource_paths);
    }
    
  private:
    std::unordered_map<std::string, std::string> _resource_paths;
};
#endif