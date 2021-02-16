#pragma once

#include <algorithm>
#include <string>

#include "FileIO.hpp"
#include "PathInitializer.hpp"


using ProjectTree = std::vector<File>;

class ProjectTreeBuilder {
    const std::string initPath_;
    ProjectTree product_;

public:
    ProjectTreeBuilder(const std::string& initPath):
        initPath_(initPath),
        product_(BuildProduct())
    {}

    ProjectTree getProduct() const { return product_; }
    
private:
    ProjectTree BuildProduct() {
        auto subFiles = ReadRecursive("");
        PathInitializer initializer("", initPath_);
        FileBuilder builder(initializer, subFiles);
        auto projectRoot = builder.getProduct();
        return Flaten(projectRoot);
    }


    std::vector<File> ReadRecursive(const std::string& targetPath) {
        auto paths = FileIO::readPaths(initPath_ + targetPath);
        std::vector<File> files;

        for (const auto& path : paths) {
            auto subFiles = ReadRecursive(targetPath + path + '/');
            PathInitializer initializer(targetPath, path);
            FileBuilder builder(initializer, subFiles);
            files.push_back(builder.getProduct());
        }
        std::sort(files.begin(), files.end(), SortCriterion_CatalogLast);
        return files;
    }
/*
    std::vector<File> ReadRecursive(const std::string& targetPath) {
        auto paths = FileIO::readPaths(targetPath);
        std::vector<File> files;
        std::vector<File> directories;
        //std::cout << targetPath << " ";

        for (const auto& path : paths) {
            auto subFiles = ReadRecursive(targetPath +  path + '/');
            auto file = ProcessData(targetPath, path, subFiles); 
            
            if (subFiles.empty()) {
                files.push_back(file);
                continue;
            }
            directories.push_back(file);
            for (const auto& subFile : subFiles) {
                directories.push_back(subFile);
            }
            //files.insert(files.end(), subFiles.begin(), subFiles.end());
        }
        for (const auto& subFile : files) {
            directories.push_back(subFile);
        }
        return directories;
    }
*/

    ProjectTree Flaten(const File& root) {
        ProjectTree result;
        result.push_back(root);
        for (const auto& file : root.subFiles_) {
            auto subResult = Flaten(file);
            result.insert(result.end(), subResult.begin(), subResult.end());
        }
        return result;
/*
            result.push_back(file);
            if (file.isCatalog()) {
            }
        }
        return result;
  */  }
    
    /*
    ProjectTree Flaten(const ProjectTree& subdirectory) {
        ProjectTree result;
        for (const auto& file : subdirectory) {
            result.push_back(file);
            if (file.isCatalog()) {
                auto subResult = Flaten(file.subFiles_);
                result.insert(result.end(), subResult.begin(), subResult.end());
            }
        }
        return result;
    }
    */

    //static File ProcessData(const std::string& targetPath, const std::string& path, std::vector<File>& subFiles) {
    //}

    static bool SortCriterion_CatalogLast(const File& f, const File& s) { 
        int test = f.isCatalog() + s.isCatalog();
        if (test % 2 == 0) {
            return SortCriterion_Alphabetical(f.name_, s.name_);
        }
        else {
            return s.isCatalog();
        }
    }

    static bool SortCriterion_Alphabetical(const std::string& f, const std::string& s) { 
        return (f < s);
    }

};

