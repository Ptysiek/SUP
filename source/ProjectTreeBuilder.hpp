#pragma once

#include <algorithm>
#include <string>

#include "DataStructures"
#include "Tools"

#include "FileBuilder.hpp"


class ProjectTreeBuilder {
    using ProjectTree = DataStructures::ProjectTree;
    const std::string initPath_;
    const ProjectTree product_;

public:
    explicit ProjectTreeBuilder(const std::string& initPath):
        initPath_(initPath),
        product_(BuildProduct())
    {}

    ProjectTree getProduct() const { return product_; }
    

private:
    ProjectTree BuildProduct() const {
        auto subFiles = BuildRecursive("", 0);
        std::sort(subFiles.begin(), subFiles.end(), SortCriterion_Depth);
        
        return subFiles;
        //FileHeader projectRoot(initPath_, subFiles);
        //return Flaten(projectRoot);
    }

    std::vector<FileHeader> BuildRecursive(const std::string& targetPath, int depth) const {
        auto paths = Tools::FileIO::readPaths(initPath_ + targetPath);
        std::vector<FileHeader> files;

        for (const auto& path : paths) {
            auto subFiles = BuildRecursive(targetPath + path + '/', depth + 1);
            
            FileBuilder builder(targetPath, path, subFiles, depth);
            files.push_back(builder.getProduct());
            
            //std::sort(subFiles.begin(), subFiles.end(), SortCriterion_CatalogLast);
            //files.insert(files.end(), subFiles.begin(), subFiles.end());

            //PathInitializer initializer(targetPath, path);
            //files.push_back(FileHeader(initializer, subFiles));
        }
        //std::sort(files.begin(), files.end(), SortCriterion_CatalogLast);
        return files;
    }

            
protected:
    ProjectTree Flaten(const FileHeader& root) const {
        ProjectTree result;
        result.push_back(root);
        //for (const auto& file : root.getSubFiles()) {
            //auto subResult = Flaten(file);
            //result.insert(result.end(), subResult.begin(), subResult.end());
        //}
        return result;
    }

    static bool SortCriterion_Depth(const FileHeader& f, const FileHeader& s) { 
        if (f.depth_ == s.depth_) {
            return SortCriterion_CatalogLast(f, s);
        }
        return (f.depth_ < s.depth_);
    }

    static bool SortCriterion_CatalogLast(const FileHeader& f, const FileHeader& s) { 
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



