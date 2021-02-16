#pragma once

#include <string>

#include "FileIO.hpp"
#include "PathInitializer.hpp"


using ProjectTree = std::vector<File>;

class ProjectTreeBuilder {
    const std::string startPath_;
    ProjectTree product_;

public:
    ProjectTreeBuilder(const std::string& startPath):
        startPath_(startPath),
        product_()
    {
        BuildProduct();
    }

    ProjectTree getProduct() const { return product_; }
    
private:
    void BuildProduct() {
        auto subfiles = ReadRecursive(startPath_);
    }

    std::vector<File> ReadRecursive(const std::string& targetPath) {
        auto paths = FileIO::readPaths(targetPath);
        std::vector<File> files;

        for (const auto& path : paths) {
            auto subfiles = ReadRecursive(path);
            auto file = ProcessData(path, subfiles); 
            files.push_back(file);
        }
        return files;
    }

    File ProcessData(const std::string& path, std::vector<File>& subFiles) {
        PathInitializer initializer(path);
        FileBuilder builder(initializer, subFiles);
        //data_.push(builder.getProduct());
        return builder.getProduct();
    }



};

