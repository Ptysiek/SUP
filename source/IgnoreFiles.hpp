#pragma once 

#include <exception>
#include <fstream>
#include <set>
#include <string>



class IgnoreFiles {
protected:
    static std::set<std::string> defaultIgnores_;
    const static std::string filename_;

    explicit IgnoreFiles() { }


public:
    static bool isIgnored(const std::string& value) { return (defaultIgnores_.find(value) != defaultIgnores_.end()); }
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
*/

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
};

const std::string IgnoreFiles::filename_ = ".supignore";

std::set<std::string> IgnoreFiles::defaultIgnores_ {
    "\n",
    "",
    " ",
    ".",
    "..",
    ".git",
    ".gitignore",
    ".notes",
    ".sup",
    "notes",
    "build",
    "tools",
    "tags",
    "README.md",
    "CMakeLists.txt"
};




