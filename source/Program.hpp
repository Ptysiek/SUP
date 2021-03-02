#pragma once

#include <iostream>

#include "DataStructures"
#include "Tools"

#include "ProjectTreeBuilder.hpp"
#include "ProjectTreeParser.hpp"
#include "GeneratorTxt.hpp"


class Program {
    const std::string targetPath_;
    const std::string outputPath_;
    // ProjectTree rawData_;

public:
    explicit Program(const std::string& target):
        targetPath_(target),
        outputPath_("sup.txt")
       // rawData_()
    {}

    void execute() {
        initializeIgnoreFiles();
        ProjectTreeBuilder builder(targetPath_);
        auto rawData_ = builder.getProduct();
        
        ProjectTreeParser parser(targetPath_, rawData_);
        auto parsedData = parser.getProduct();
        
        for (const auto& file : parsedData) {
            std::cout 
                << file.depth_ << "\t"
                << file.getPath() << "\t\t" 
                << file.getName() << "\t\t" 
                << file.getFormat() << "\t\t" << file.getSubFiles().size() << "\n";
            //std::cout << file.path_ << "  " << file.name_ << "  " << file.format_ << "\n";
            //std::cout << file.path_ << file.name_ << file.format_ << "\n";
        }
        GeneratorTxt generator(targetPath_, parsedData);
        Tools::FileIO::saveToFile(outputPath_, generator.buildFile());
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


