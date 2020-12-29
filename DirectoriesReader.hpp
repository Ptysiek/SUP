#pragma once 


#include <dirent.h>
#include <iostream>
#include <string>
#include <vector>






class DirectoriesReader {


    std::vector<std::string> ignoreDirectories_ {
        ".",
        "..",
        ".git",
        ".gitignore",
        ".notes",
        "notes",
        "build",
        "tools",
        "README.md",
        "CMakeLists.txt"
    };


public:
    std::vector<std::string> getDirectories(std::string startpath) {
        std::vector<std::string> result;

        DIR* directory;
        directory = opendir(startpath.c_str());

        if (!directory) {
            return result;
        }

        struct dirent* entry;
        while ((entry = readdir(directory)) != NULL) {
            std::string data = entry->d_name;

            
            if (!CheckIgnoreDirectories(data)) {
                continue;
            }
            auto tmpVctr = getDirectories(startpath + "/" + data);
            if (tmpVctr.size() > 0) {
                for (const auto& record : tmpVctr) {
                    result.push_back(data + "/" + record);
                }
            }
            else {
                result.push_back(data);
            }        
        }

        closedir(directory);
        return result;
    }
private:
    bool CheckIgnoreDirectories(std::string data) {
        for (const auto& record : ignoreDirectories_) {
            if (data == record) {
                return false;
            }
        }
        return true;
    }

};





