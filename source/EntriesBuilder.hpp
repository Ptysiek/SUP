#pragma once

#include <chrono>
#include <string>

#include "ProjectTree.hpp"


class EntriesBuilder {

public:
    static std::string getHeader() {
        return "Author of SUP-SeeYourPoint: Kacu Kacper Kaleta [https://github.com/Ptysiek]\n";
    }

    static std::string getDate() {
        using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
        TimePoint thisPoint = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(thisPoint);
        std::string date = std::ctime(&t);
        return date;
    }

    static std::string getTableOfContents(const ProjectTree& projTree) {
        std::string result = "";
        result += "_____________________________________________\n";
        result += "Table of contents:   ------------------------\n";
        result += getTableOfContentsData(projTree.getDirectories());
    
        return result;
    }
    
private:
    static std::string getTableOfContentsData(const std::vector<File>& directories, size_t tab=1) {
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
                result += getTableOfContentsData(file.files_, tab + 1);   
                result += getTabs(tab);
            }
            else {
                result += file.name_;
            }
            result += "\n";
        }
        return result;
    }

    static std::string getTabs(size_t tab=1) {
        std::string result = "\t";
        for (size_t i = 1; i < tab; ++i) {
            result += "|\t";
        }
        return result;
    }
};

