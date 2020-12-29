#pragma once

#include <chrono>
#include <fstream>
#include <string>
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
        if (directories_.size() < 1) {
            return false;
        }

        std::ofstream file(filename_);
        if (!file || !file.is_open()) {
            return false;
        }
        
        file << getHeader();
        file << "File generation date: " << getDate();

        file << "\n\n";
        file << "_____________________________________________\n";
        file << "Table of contents:---------------------------\n";
        for (const auto& record : directories_) {
            file << "\t" << record << "\n";
        }
        
        file.close();
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


};

