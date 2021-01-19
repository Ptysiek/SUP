#pragma once

#include "File.hpp"



class ProjectTree {
    std::vector<File> directories_;
    std::vector<std::string> directoriesPaths_;


public:
    explicit ProjectTree(): directories_(), directoriesPaths_() {}
    
    std::vector<File> getDirectories() const { return directories_; }
    std::vector<std::string> getDirectoriesPaths() const { return directoriesPaths_; }

    void setDirectories(std::vector<File>& directories) {
        directories_ = directories;
        sortDirectories(directories_);
        setDirectoriesPaths(directories_);
    }


private:
    void setDirectoriesPaths(const std::vector<File>& directories) {
        directoriesPaths_ = getPaths(directories, "");  
    }

    std::vector<std::string> getPaths(const std::vector<File>& directories, const std::string& path) const {
        std::vector<std::string> result;
        
        for (const auto& file : directories) {
            if (file.isCatalog_) {
                auto subFiles = getPaths(file.files_, path + file.name_ + "/");
                result.insert(result.end(), subFiles.begin(), subFiles.end() );
            }
            else {
                result.push_back(path + file.name_);
            }
        }
        return result;
    }



    void sortDirectories(std::vector<File>& directories) {
        std::sort(directories.begin(), directories.end(), SortCriterion);

        for (auto& subDir : directories) {
            if (subDir.isCatalog_) {
                sortDirectories(subDir.files_);
            }
        }
    }
    
    static bool SortCriterion(const File& f, const File& s) { 
        int test = f.isCatalog_ + s.isCatalog_;
        if (test % 2 == 0) {
            return SecondSortCriterion_Alphabetical(f.name_, s.name_);
        }
        else {
            return s.isCatalog_;
        }
    }

    static bool SecondSortCriterion_Alphabetical(const std::string& f, const std::string& s) { 
        return (f < s);
    }
}; 

