#pragma once

#include <string>
#include <vector>

#include "PathInitializer.hpp"


struct FileHeader {
    std::string initPath_;
    std::string name_;
    std::string path_;
    std::string format_;
    std::vector<FileHeader> subFiles_;

    int depth_;


public:
    explicit FileHeader(const std::string& path, const std::vector<FileHeader>& subFiles):
        initPath_(),
        name_(path),
        path_(),
        format_(),
        subFiles_(subFiles),
        depth_()
    {}

    explicit FileHeader(
        const std::string& initPath,
        const std::string& name,
        const std::string& path,
        const std::string& format,
        const std::vector<FileHeader>& subFiles,
        const int depth):
        initPath_(initPath),
        name_(name),
        path_(path),
        format_(format),
        subFiles_(subFiles),
        depth_(depth)
    {}

    std::string getName() const { return name_; }
    std::string getPath() const { return path_; }
    std::string getFormat() const { return format_; }
    std::string getFile() const { return initPath_ + path_ + name_ + format_; }
    std::vector<FileHeader> getSubFiles() const { return subFiles_; }

    bool isCatalog() const { return !subFiles_.empty(); }
};

