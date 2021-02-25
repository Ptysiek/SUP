#pragma once

#include <algorithm>
#include <string>

#include "Tools"
#include "PathInitializer.hpp"


using ProjectTree = std::vector<File>;

class ProjectTreeBuilder {
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
        auto subFiles = ReadRecursive("");
        File projectRoot(initPath_, subFiles);
        return Flaten(projectRoot);
    }

    std::vector<File> ReadRecursive(const std::string& targetPath) const {
        auto paths = Tools::FileIO::readPaths(initPath_ + targetPath);
        std::vector<File> files;

        for (const auto& path : paths) {
            auto subFiles = ReadRecursive(targetPath + path + '/');
            PathInitializer initializer(targetPath, path);
            files.push_back(File(initializer, subFiles));
        }
        std::sort(files.begin(), files.end(), SortCriterion_CatalogLast);
        return files;
    }


protected:
    ProjectTree Flaten(const File& root) const {
        ProjectTree result;
        result.push_back(root);
        for (const auto& file : root.getSubFiles()) {
            auto subResult = Flaten(file);
            result.insert(result.end(), subResult.begin(), subResult.end());
        }
        return result;
    }

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



