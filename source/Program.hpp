#pragma once

#include <iostream>

#include "GeneratorTxt.hpp"
#include "ProjectTreeBuilder.hpp"
#include "Tools"


class Program {
    const std::string targetPath_;
    const std::string outputPath_;


public:
    explicit Program(const std::string& target):
        targetPath_(target),
        outputPath_("sup.txt")
    {}

    void execute() {
        initializeIgnoreFiles();

        ProjectTreeBuilder builder(targetPath_);
        auto project = builder.getProduct();
        
        for (const auto& file : project) {
            std::cout 
                << file.getDepth() << "\t"
                << file.countSubFiles() << "\t"
                << file.countSubFilesRecursive() << "\t"
                << file.getInitPath() << "\t\t" 
                << file.getPath() << "\t\t" 
                << file.getName() << "   \t\t" 
                << file.getFormat() << "\n";  
        }
        GeneratorTxt generator(targetPath_, project);
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


