#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>

#include "File.hpp"
#include "StateMachine.hpp"


class DocumentationGenerator {
    //using FullName = std::string;
    //using PartName = std::string;
    using ProjectMap = std::vector<std::string>;

    const std::string startPath_;
    const std::string filename_;

    ProjectTree projTree_;



public:
    explicit DocumentationGenerator(const std::string& startPath):
        startPath_(startPath),
        filename_("sup.txt"),
        directories_()
    {}



    bool generate() {
        std::string data = "";

        data += getHeader();
        data += "File generation date: " + getDate();

        data += "\n\n";
        data += getTableOfContents();

        auto dirs = getDirectories(directories_);

        std::map<std::string,std::string> allFilesData;
        for (const auto& file : dirs) {
            auto fileData_tmp = readFromFile(startPath_ + file);
            allFilesData[file] = fileData_tmp; 
            //data += fileData_tmp;
            //data += "\n\n";
        }
        StateMachine sm;
        data += sm.Process(allFilesData);

        std::ofstream output(filename_);
        if (!output || !output.is_open()) {
            return false;
        }
        output << data;

        output.close();
        return true;
    }

private:
    std::string geTableOfContents() {
        std::string result = "";
        result += "_____________________________________________\n";
        result += "Table of contents:   ------------------------\n";
        result += getTableOfContentsData(directories_);
    
        return result;
    }



    std::string readFromFile(const std::string& path) {
        //std::vector<std::string> fileData;
        //fileData.reserve(500);
        std::string fileData = "";

        std::ifstream readFile(path);
        std::string tmp;
        while (std::getline(readFile, tmp)) {
            if (tmp == "\n" || tmp == "") {
                continue;
            }
            fileData += tmp;
            fileData += "\n";
        }
        /*
        while (readFile) {
            std::string tmp;
            readFile >> tmp;
            //fileData.push_back(tmp);
            fileData += tmp;
            fileData += ' ';
        }
        //*/
        readFile.close();
        
        return fileData;
    }


    std::string getHeader() {
        return "Author of SUP-SeeYourPoint: Kacu Kacper Kaleta [https://github.com/Ptysiek]\n";
    }

    std::string getDate() {
        using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
        TimePoint thisPoint = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(thisPoint);
        std::string date = std::ctime(&t);
        return date;
    }


    std::string getTableOfContents(std::vector<File> directories, size_t tab=1) {
        if (directories.size() < 1) {
            throw std::logic_error("DocumentationGenerator::getTableOfContents()");
        }
        
        std::string result = "";
        for (const auto& file : directories) {
            result += getTabs(tab);
            
            if (file.isCatalog_) {
                result += "[";
                result += file.name_;
                result += "]\n";
                result += getTableOfContents(file.files_, tab + 1);   
                result += getTabs(tab);
            }
            else {
                result += file.name_;
            }
            result += "\n";
        }
        return result;
    }

    std::string getTabs(size_t tab=1) {
        std::string result = "\t";
        for (size_t i = 1; i < tab; ++i) {
            result += "|\t";
        }
        return result;
    }
    
    std::vector<std::string> getDirectories(const std::vector<File>& directories, const std::string& path="") {
        std::vector<std::string> result;
        
        for (const auto& file : directories) {
            if (file.isCatalog_) {
                auto subFiles = getDirectories(file.files_, path + file.name_ + "/");
                result.insert(result.end(), subFiles.begin(), subFiles.end() );
            }
            else {
                result.push_back(path + file.name_);
            }
        }
        return result;
    }


};

