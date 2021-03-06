#pragma once

#include <iostream>

#include "GeneratorTxt.hpp"
#include "ProjectBuilder.hpp"
#include "ProgramInitializer.hpp"
#include "Tools"


class Program {
    const ProgramInitializer flagSupport_;
    const std::string targetPath_;
    const std::string outputPath_;


public:
    explicit Program(const ProgramInitializer& target):
        flagSupport_(target),
        targetPath_(target.getPath()),
        outputPath_("sup.txt")
    {}

    void execute() {
        initializeIgnoreFiles();

        ProjectBuilder builder(targetPath_);
        auto project = builder.getProduct();
        
        for (const auto& file : project) {
            const std::string tab(file.getDepth() * 3, ' '); 
            std::cout << tab << file.getFile() << "\n"; 
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


