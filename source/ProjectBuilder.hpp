#pragma once

#include <algorithm>
#include <string>

#include "DataStructures"
#include "FileDataBuilder.hpp"
#include "FileBuilder.hpp"
#include "Tools"


class ProjectBuilder {
    using Project = DataStructures::Project; 
    
    const std::string initPath_;
    const Project product_;


public:
    explicit ProjectBuilder(const std::string& initPath):
        initPath_(initPath),
        product_(BuildProduct())
    {}

    Project getProduct() const { return product_; }
    

private:
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    Project BuildProduct() const {
        auto project = BuildProductStructure();
        project = UpdateProjectWithData(project);
        return project;
    }

    Project UpdateProjectWithData(Project& project) const {
        for (auto& file : project) {
            FileDataBuilder builder(file);
            if (builder.dataExist()) {
                file.setData(builder.getProduct());
            }
        }
        return project;
    }

    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    Project BuildProductStructure() const {
        auto subFiles = BuildRecursive("", 1);
        File root = FileBuilder::buildRoot(initPath_, subFiles);
        return FlatenRecursive(root);
    }

    std::vector<File> BuildRecursive(const std::string& targetPath, int depth) const {
        auto paths = Tools::FileIO::readPaths(initPath_ + targetPath);
        std::vector<File> files;

        for (const auto& path : paths) {
            auto subFiles = BuildRecursive(targetPath + path + '/', depth + 1);
            
            FileBuilder builder(initPath_, targetPath, path, subFiles, depth);
            files.emplace_back(builder.getProduct());
        }
        std::sort(files.begin(), files.end(), SortCriterion_CatalogLast);
        return files;
    }

    Project FlatenRecursive(const File& root) const {
        Project result;
        result.emplace_back(root);
        for (const auto& file : root.getSubFiles()) {
            auto subResult = FlatenRecursive(file);
            result.insert(result.end(), subResult.begin(), subResult.end());
        }
        return result;
    }

    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    static bool SortCriterion_CatalogLast(const File& f, const File& s) { 
        int test = f.isCatalog() + s.isCatalog();
        if (test % 2 == 0) {
            return SortCriterion_Alphabetical(f.getName(), s.getName());
        }
        return s.isCatalog();
    }

    static bool SortCriterion_Alphabetical(const std::string& f, const std::string& s) { 
        return (f < s);
    }
};



