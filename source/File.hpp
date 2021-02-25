#pragma once

#include <string>
#include <vector>

#include "PathInitializer.hpp"


class File {
    std::string name_;
    std::string path_;
    std::string format_;
    std::vector<File> subFiles_;


public:
    explicit File(const std::string& path, const std::vector<File>& subFiles):
        name_(path),
        path_(),
        format_(),
        subFiles_(subFiles)
    {}
    explicit File(const PathInitializer& target, const std::vector<File>& subFiles):
        name_(target.getName()),
        path_(target.getPath()),
        format_(target.getFormat()),
        subFiles_(subFiles)
    {}

    std::string getName() const { return name_; }
    std::string getPath() const { return path_; }
    std::string getFormat() const { return format_; }
    std::string getFile() const { return path_ + name_ + format_; }
    std::vector<File> getSubFiles() const { return subFiles_; }

    bool isCatalog() const { return !subFiles_.empty(); }
};

