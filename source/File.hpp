#pragma once

#include <vector>
#include <iostream>

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
        fullname_(path+name),
        files_()
    { }

    std::string to_string() {
        return "(" 
            + name_ + ", "
            + path_ + ", "
            + fullname_ + ")";
    }


    /*
    explicit File(std::string& name, std::vector<File>& files):
        isCatalog_(true),
        name_(name),
        files_(files)
    {}
    */
};


