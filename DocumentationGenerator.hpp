#pragma once

#include <chrono>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>

#include "DataStructures.hpp"


class DocumentationGenerator {

    const std::string filename_{"sup.txt"};
    std::vector<FilePtr> directories_;



public:
    void setDirectoriesVector(std::vector<FilePtr>& vctr) {
        directories_ = vctr;
    }


    

    bool generate() {
        std::ofstream output(filename_);
        if (!output || !output.is_open()) {
            return false;
        }
        
        output << getHeader();
        output << "File generation date: " << getDate();

        output << "\n\n";
        output << "_____________________________________________\n";
        output << "Table of contents:---------------------------\n";
        output << getDirectories();
        
        output.close();
        return true;
    }

private:
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


    std::string getDirectories() {
        return getDirectories(directories_);
    }

    std::string getDirectories(std::vector<FilePtr> directories, size_t tab=1) {
        if (directories.size() < 1) {
            throw std::logic_error("DocumentationGenerator::getDirectories()");
        }
        
        std::string result = "";

        for (const auto& file : directories) {
            result += getTabs(tab);
            result += file->name_;
            
            if (file->isCatalog()) {
                result += "   [DIR]\n";
                result += getDirectories(file->getFiles(), tab + 1);   
                result += getTabs(tab);
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

};

