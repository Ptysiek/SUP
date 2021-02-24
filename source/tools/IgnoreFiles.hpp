#pragma once 

#include <algorithm>
#include <exception>
#include <set>
#include <string>



namespace Tools {
class IgnoreFiles {
    const static std::string filename_;
    const static std::set<std::string> alwaysIgnores_;
    const static std::set<std::string> formatIgnores_;
    static std::set<std::string> defaultIgnores_;
    static std::set<std::string> ignored_;

    explicit IgnoreFiles() { }


public:
    static void setIgnoreFiles(const std::vector<std::string>& vctr) {
        defaultIgnores_ = std::set<std::string>(vctr.begin(), vctr.end());
    }
    
    static std::string getIgnoreFileName() { return filename_; }

    static std::set<std::string> getDefaultIgnoreFiles() { return defaultIgnores_; }

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
    
    static std::vector<std::string> pickoutAlwaysIgnored(const std::vector<std::string>& vctr) {
        std::vector<std::string> result;
        result.reserve(vctr.size());
        std::copy_if(vctr.begin(), vctr.end(), result.begin(), [](auto val){return !isAlwaysIgnored(val);});
        return result;
    }

private: 
/*
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



