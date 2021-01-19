#pragma once

#include "File.hpp"



class ProjectTree {
    std::vector<File> directories_;
    std::vector<std::string> directoriesPaths_;


public:
    explicit ProjectTree(): 
        directories_(), 
        directoriesPaths_() 
    {}
    
    std::vector<File> getDirectories() const { return directories_; }
    std::vector<std::string> getDirectoriesPaths() const { return directoriesPaths_; }

    void setDirectories(const std::vector<File>& directories) {
        directories_ = directories;
        SortDirectories_Recursive(directories_);
        directoriesPaths_ = EnlistDirectoriesPaths_Recursive(directories_, "");  
    }


private:
    static std::vector<std::string> EnlistDirectoriesPaths_Recursive(
        const std::vector<File>& directories, 
        const std::string& path)  
    {
        std::vector<std::string> result;
        
        for (const auto& file : directories) {
            if (file.isCatalog_) {
                auto subFiles = EnlistDirectoriesPaths_Recursive(file.files_, path + file.name_ + "/");
                result.insert(result.end(), subFiles.begin(), subFiles.end() );
            }
            else {
                result.push_back(path + file.name_);
            }
        }
        return result;
    }

    static void SortDirectories_Recursive(std::vector<File>& directories) {
        std::sort(directories.begin(), directories.end(), SortCriterion);

        for (auto& subDir : directories) {
            if (subDir.isCatalog_) {
                SortDirectories_Recursive(subDir.files_);
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

