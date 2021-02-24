#pragma once

#include <iostream>

#include "File.hpp"
#include "Tools"
#include "ParsedFile.hpp"
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
        initializeIgnoreFiles();
        ProjectTreeBuilder builder(targetPath_);
        data_ = builder.getProduct();
        
        for (const auto& file : data_) {
            std::cout << file.getPath() << "  " 
                << file.getName() << "  " 
                << file.getFormat() << "  " << file.getSubFiles().size() << "\n";
            //std::cout << file.path_ << "  " << file.name_ << "  " << file.format_ << "\n";
            //std::cout << file.path_ << file.name_ << file.format_ << "\n";
        }
    }


private:
    void initializeIgnoreFiles() {
        using Tools::Converter;
        using Tools::FileIO; 
        using Tools::IgnoreFiles; 

        auto fileName = IgnoreFiles::getIgnoreFileName();
        if (FileIO::fileExist(fileName)) {
            auto data = FileIO::readFile(fileName);      
            data = IgnoreFiles::pickoutAlwaysIgnored(data);
            IgnoreFiles::setIgnoreFiles(Converter::to_set(data));
        }
        else {
            auto data = IgnoreFiles::getDefaultIgnoreFiles();
            FileIO::saveToFile(fileName, Converter::to_fileData(data));
        }
    }
};


