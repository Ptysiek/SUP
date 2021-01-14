#pragma once 

#include <dirent.h>
#include <memory>
#include <string>
#include <vector>

#include "DataStructures.hpp"



class DirectoriesReader {
    const static std::vector<std::string> ignoreDirectories_;

    explicit DirectoriesReader() { }


public:
    static std::vector<File> getDirectories(std::string startpath) {
        std::vector<File> result;

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
                File tmp(data, tmpVctr);
                result.push_back(tmp);
            }
            else {
                File tmp(data);
                result.push_back(tmp);
            }        
        }
        closedir(directory);
        return result;
    }

private:
    static bool CheckIgnoreDirectories(std::string data) {
        for (const auto& record : ignoreDirectories_) {
            if (data == record) {
                return false;
            }
        }
        return true;
    }
};


const std::vector<std::string> DirectoriesReader::ignoreDirectories_ {
    "\n",
    "",
    ".",
    "..",
    ".git",
    ".gitignore",
    ".notes",
    "notes",
    "build",
    "tools",
    "tags",
    "README.md",
    "CMakeLists.txt"
};




