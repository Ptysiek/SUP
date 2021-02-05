#pragma once

#include <dirent.h>
#include <string>
#include <vector>


class FileIO {



public:
    static std::vector<std::string> readPaths(const std::string& targetPath) {
        std::vector<std::string> result;

        DIR* directory;
        directory = opendir(targetPath.c_str());

        if (!directory) {
            return result;
        }

        struct dirent* entry;
        while ((entry = readdir(directory)) != NULL) {
            const std::string data = entry->d_name;

            result.push_back(data);
        }
        closedir(directory);
        return result;
    }





};

