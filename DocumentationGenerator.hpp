#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>

#include "DataStructures.hpp"


class DocumentationGenerator {

    const std::string filename_{"sup.txt"};
    std::vector<File> directories_;



public:
    void setDirectoriesVector(std::vector<File>& vctr) {
        directories_ = vctr;
        sortDirectories(directories_);
    }

    void sortDirectories(std::vector<File>& directories) {
        std::sort(directories.begin(), directories.end(), SortCriterion);

        for (auto& subDir : directories) {
            if (subDir.isCatalog_) {
                sortDirectories(subDir.files_);
            }
        }
    }
    
    static bool SortCriterion(const File& f, const File& s) { 
        int test = f.isCatalog_ + s.isCatalog_;
        if (test % 2 == 0) {
            return SecondSortCriterion_Alphabetical(f.name_, s.name_);
        }
        else {
            return s.isCatalog_;
        }
    }
    static bool SecondSortCriterion_Alphabetical(const std::string& f, const std::string& s) { 
        return (f < s);
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
        output << "Table of contents:   ------------------------\n";
        output << getTableOfContents(directories_);
        
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


    std::string getTableOfContents(std::vector<File> directories, size_t tab=1) {
        if (directories.size() < 1) {
            throw std::logic_error("DocumentationGenerator::getDirectories()");
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

};

