#pragma once

#include <iostream>

#include "File.hpp"
#include "Tools"
#include "ProjectTreeBuilder.hpp"


class Program {
    const std::string targetPath_;
    ProjectTree data_;

public:
    explicit Program(const std::string& target):
        targetPath_(target),
        data_()
    {}

    void execute() {
        ProjectTreeBuilder builder(targetPath_);
        data_ = builder.getProduct();
        
        for (const auto& file : data_) {
            std::cout << file.getPath() << "  " 
                << file.getName() << "  " 
                << file.getFormat() << "  " << file.getSubFiles().size()<< "\n";
            //std::cout << file.path_ << "  " << file.name_ << "  " << file.format_ << "\n";
            //std::cout << file.path_ << file.name_ << file.format_ << "\n";
        }
    }

private:
    void initializeIgnoreFiles() {
        if (Tools::FileIO::fileExist(Tools::IgnoreFiles::getIgnoreFileName())) {
        }
    }


};

