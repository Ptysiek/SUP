#pragma once

#include <chrono>
#include <fstream>
#include <string>
#include <vector>


class DocumentationGenerator {

    std::vector<std::string> directories_;



public:
    void setDirectoriesVector(std::vector<std::string> vctr) {
        directories_ = vctr;
    }

    void generate() {

        if (directories_.size() > 1) {
            return;
        }
    }

private:
    std::string getHeader() {
        return "Author: Kacu Kacper Kaleta [https://github.com/Ptysiek]";
    }

    std::string getDate() {
        using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
        TimePoint thisPoint = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(thisPoint);
        std::string date = std::ctime(&t);
        return date;
    }


};

