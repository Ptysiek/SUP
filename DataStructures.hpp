#pragma once

#include <vector>


struct File {
    explicit File(std::string& name): 
        isCatalog_(false),
        name_(name)
    {}
    explicit File(std::string& name, std::vector<File>& files):
        isCatalog_(true),
        name_(name),
        files_(files)
    {}

    bool isCatalog_;
    std::string name_;
    std::vector<File> files_; 

    //bool isCatalog() const { return (files_.size() > 0); }
};


