#pragma once 

#include <dirent.h>
#include <exception>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "File.hpp"



class DirectoriesReader {
protected:
    static std::set<std::string> ignoreDirectories_;

    explicit DirectoriesReader() { }


public:
    static std::vector<File> getDirectories(const std::string& startpath) {
        return GetDirectoriesRecursive(startpath);
    }
    


private:
    static std::vector<File> GetDirectoriesRecursive(std::string startpath) {
        startpath = ConditionalSlashAppend(startpath);
        auto directoryNames = ReadDirectories(startpath);
        auto files = MakeFiles(directoryNames, startpath);

        for (auto& file : files) {
            auto subdirectories = GetDirectoriesRecursive(startpath + file.name_);
            if (subdirectories.size() > 0) {
                file.isCatalog_ = true;
                file.files_ = subdirectories;
            }
        }
        return files;
    }

    static std::vector<std::string> ReadDirectories(const std::string& path) {
        std::vector<std::string> directoryNames;

        DIR* directory;
        directory = opendir(path.c_str());

        if (!directory) {
            return directoryNames;
        }

        struct dirent* entry;
        while ((entry = readdir(directory)) != NULL) {
            std::string data = entry->d_name;

            if (IgnoreListContains(data)) {
                continue;
            }
            directoryNames.push_back(data);
        }
        closedir(directory);
        return directoryNames;
    }


protected:
    static std::string ConditionalSlashAppend(const std::string& startpath) {
        if (size_t size = startpath.size(); size > 0) {
            return (startpath[size-1] == '/')? startpath : startpath + '/';
        }
        throw std::logic_error("DirectoriesReader::ConditionalSlashAppend() startpath is empty");
    }

    static bool IgnoreListContains(const std::string& data) {
        return (ignoreDirectories_.find(data) != ignoreDirectories_.end());
    }

    static File MakeFile(const std::string& dirname, const std::string& startpath) {
        return File(dirname, ConditionalSlashAppend(startpath));
    }

    static std::vector<File> MakeFiles(
            const std::vector<std::string>& directoryNames, 
            const std::string& startpath) 
    {
        std::vector<File> files;

        for (const auto& dirname : directoryNames) {
            files.push_back(MakeFile(dirname, startpath)); 
        }
        return files;
    }
};

std::set<std::string> DirectoriesReader::ignoreDirectories_ {
    "\n",
    "",
    " ",
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




