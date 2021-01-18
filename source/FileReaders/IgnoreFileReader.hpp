#pragma once 

#include <exception>
#include <fstream>
#include <set>
#include <string>



class IgnoreFileReader {
protected:
    const static std::set<std::string> defaultIgnores_;
    const static std::string filename_;

    explicit IgnoreFileReader() { }


public:
    static std::set<std::string> getFilesToIgnore() {
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
};

const std::string IgnoreFileReader::filename_ = ".supignore";

const std::set<std::string> IgnoreFileReader::defaultIgnores_ {
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




