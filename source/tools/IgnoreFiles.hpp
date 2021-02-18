#pragma once 

#include <exception>
#include <set>
#include <string>



namespace Tools {
class IgnoreFiles {
    const static std::string filename_;
    const static std::set<std::string> alwaysIgnores_;
    const static std::set<std::string> formatIgnores_;
    static std::set<std::string> defaultIgnores_;
    static std::set<std::string> ignores_;

    explicit IgnoreFiles() { }


public:
    static std::string getIgnoreFileName() { return filename_; }

    static bool isAlwaysIgnored(const std::string& value) {
        return (alwaysIgnores_.find(value) != alwaysIgnores_.end());
    }
    static bool isFormatIgnored(const std::string& format) {
        return (formatIgnores_.find(format) != formatIgnores_.end());
    }
    static bool isIgnored(const std::string& value) {
        if (isAlwaysIgnored(value)) {
            return true;
        }
        if (isFormatIgnored(value)) {
            return true;
        }
        return (defaultIgnores_.find(value) != defaultIgnores_.end());
    }
/*
    static std::set<std::string> readFilesToIgnore() {
        std::ifstream readFile(filename_);
        
        if (!readFile || !readFile.is_open()) {
            GenerateDefaultFile();
            return defaultIgnores_;
        }

        std::set<std::string> fileData;
        std::string record;

        while (std::getline(readFile, record)) {
            if (record == "\n" || record == "") {
                continue;
            }
            fileData.insert(record);
        }
        readFile.close();   
        defaultIgnores_ = fileData;
        return fileData;
    }

private: 

    static void GenerateDefaultFile() {
        std::ofstream output(filename_);
        if (!output || !output.is_open()) {
            throw std::logic_error("IgnoreFileReader::getFilesToIgnore() Failed to generate");
        }
        
        for (const auto& record : defaultIgnores_) {
            output << record << "\n";
        }
        output.close();
    }
    */
};

const std::string IgnoreFiles::filename_ = ".supignore";

const std::set<std::string> IgnoreFiles::formatIgnores_ {
    ".ut.cpp",
    ".ut.hpp"
};

const std::set<std::string> IgnoreFiles::alwaysIgnores_ {
    "\n",
    "",
    ".",
    "..",
    "./",
    "../"
};

std::set<std::string> IgnoreFiles::defaultIgnores_ {
    ".git",
    ".gitignore",
    ".notes",
    ".sup",
    "notes",
    "build",
    "plugins",
    "tags",
    "README.md",
    "CMakeLists.txt"
};
} // namespace Tools



