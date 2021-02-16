#pragma once

#include <dirent.h>
#include <fstream>
#include <string>
#include <vector>

#include "IgnoreFiles.hpp"

class FileIO {
    FileIO() {}

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
            if (IgnoreFiles::isIgnored(data)) {
                continue;
            }
            result.push_back(data);
        }
        closedir(directory);
        return result;
    }

    static void readFile(const std::string& path) {
        std::ifstream readFile(path);        
        if (!readFile || !readFile.is_open()) {
            readFile.close();
            throw std::logic_error("Cannot read given file path: " + path + "\n");
        }
        while (true) {
            std::string record;
            if (!std::getline(readFile, record)) {
                break;
            }
        }
        readFile.close();
        //return result;
    }

    static void saveToFile(const std::string& path, const std::string& data) {
        std::ofstream output(path);
        if (!output || !output.is_open()) {
            throw std::logic_error("Cannot save to file: " + path + "\n");
        }
        output << data;
        output.close();
    }
};




