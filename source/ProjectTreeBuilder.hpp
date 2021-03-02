#pragma once

#include <algorithm>
#include <string>

#include "Tools"

#include "FileBuilder.hpp"
#include "FileDataBuilder.hpp"


class ProjectTreeBuilder {
    using ProjectTree = std::vector<File>;
    //using ProjectTree = DataStructures::ProjectTree;
    const std::string initPath_;
    const ProjectTree product_;

public:
    explicit ProjectTreeBuilder(const std::string& initPath):
        initPath_(initPath),
        product_(BuildProduct())
    {}

    ProjectTree getProduct() const { return product_; }
    

private:
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    ProjectTree BuildProduct() const {
        auto project = BuildProductStructure();
        project = UpdateProjectWithData(project);
        return project;
    }

    ProjectTree UpdateProjectWithData(ProjectTree& project) const {
        for (auto& file : project) {
            FileDataBuilder builder(file);
            if (builder.productExist()) {
                auto data = builder.getProduct();
                file.setData(data);
            }
        }
        return project;
    }

    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    ProjectTree BuildProductStructure() const {
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

    ProjectTree FlatenRecursive(const File& root) const {
        ProjectTree result;
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
        else {
            return s.isCatalog();
        }
    }

    static bool SortCriterion_Alphabetical(const std::string& f, const std::string& s) { 
        return (f < s);
    }
};



