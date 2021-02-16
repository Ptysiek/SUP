#pragma once

#include <string>
#include <vector>

#include "PathInitializer.hpp"


struct File {
    std::string name_;
    std::string path_;
    std::string format_;

    std::vector<File> subFiles_;

    explicit File(const PathInitializer& target, const std::vector<File>& subFiles):
        name_(target.getName()),
        path_(target.getPath()),
        format_(target.getFormat()),
        subFiles_(subFiles)
    {}
    bool isCatalog() const { return !subFiles_.empty(); }


};

