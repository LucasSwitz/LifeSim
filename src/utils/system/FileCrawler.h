#ifndef FILECRAWLER_H
#define FILECRAWLER_H

#include <experimental/filesystem>
#include <map>

class FileCrawler
{
  public:
    template <typename T>
    void Crawl(std::string file_crawl_root, T &map)
    {
        for (auto &full_file_path : directory_iterator(file_crawl_root))
        {
            path current_path = full_file_path.path();

            if (is_regular_file(current_path))
            {
                std::string current_path_string = current_path.string();
                std::string current_file_name = current_path.filename().string();
                map.insert(std::make_pair(current_file_name, current_path_string));
            }
            else
            {
                Crawl(current_path, map);
            }
        }
    }
};

#endif