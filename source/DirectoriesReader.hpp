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

    static std::string RemoveSlashOnEnd(const std::string& dirname) {
        if (dirname.size() == 0) {
            return dirname;
        }
        
        std::string directoryName = "";
        size_t dirname_size = dirname.size()-1;
        
        for (size_t i = 0; i < dirname_size; ++i) {
            directoryName += dirname[i];
        }
        if (dirname[dirname_size] != '/') {
            directoryName += dirname[dirname_size];
        }

        return directoryName;
    }

    static bool IgnoreListContains(const std::string& data) {
        return (ignoreDirectories_.find(data) != ignoreDirectories_.end());
    }

    static File MakeFile(const std::string& dirname, const std::string& startpath) {
        const std::string directoryName = RemoveSlashOnEnd(dirname);
        TestDirname(directoryName);
        return File(directoryName, ConditionalSlashAppend(startpath));
    }
    static void TestDirname(const std::string& dirname) {
        if (dirname.empty()) {
            throw std::logic_error("DirectoriesReader::MakeFile()::TestDirname() directoryName is empty");
        }

        for (size_t i = 1; i < dirname.size(); ++i) {
            if (dirname[i - 1] == '/' && dirname[i] == '/') {
                throw std::logic_error("DirectoriesReader::MakeFile()::TestDirname() double slash");
            }
        }
        if (dirname == ".." || dirname == "../" || dirname == "." || dirname == "./") {
            throw std::logic_error("DirectoriesReader::MakeFile()::TestDirname() given navigation directory");
        }
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




