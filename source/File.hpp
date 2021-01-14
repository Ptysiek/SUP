#pragma once

#include <vector>


struct File {
    bool isCatalog_;
    std::string name_;
    std::string path_;
    std::string fullname_;
    std::vector<File> files_; 


    explicit File(const std::string& name, const std::string& path): 
        isCatalog_(false),
        name_(name),
        path_(path),
        fullname_(name+path)
    {}


    /*
    explicit File(std::string& name, std::vector<File>& files):
        isCatalog_(true),
        name_(name),
        files_(files)
    {}
    */
};


