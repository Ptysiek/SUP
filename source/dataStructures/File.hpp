#pragma once

#include <string>
#include <vector>

#include "PathInitializer.hpp"


class File {
    int depth_;
    std::string initPath_;
    std::string path_;
    std::string name_;
    std::string format_;
    std::vector<File> subFiles_;


public:
    File(  
        const int depth,
        const std::string& initPath,
        const std::string& path,
        const std::string& name,
        const std::string& format,
        const std::vector<File>& subFiles
        ):
        depth_(depth),
        initPath_(initPath),
        path_(path),
        name_(name),
        format_(format),
        subFiles_(subFiles)
    {}

    int getDepth() const { return depth_; }
    std::string getInitPath() const { return initPath_; }
    std::string getPath() const { return path_; }
    std::string getName() const { return name_; }
    std::string getFormat() const { return format_; }
    std::string getFile() const { return initPath_ + path_ + name_ + format_; }
    std::vector<File> getSubFiles() const { return subFiles_; }

    bool isCatalog() const { return !subFiles_.empty(); }
};

