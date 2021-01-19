#pragma once

#include "File.hpp"



class ProjectTree {

    std::vector<File> directories_;

public:
    std::vector<File> getDirectories() const { return directories_; }

    void setProjectTree(std::vector<File>& directories) {
        directories_ = directories;
        sortDirectories(directories_);
    }

private:
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

