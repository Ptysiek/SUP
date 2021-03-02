#pragma once

#include <string>
#include <vector>

#include "FileData.hpp"


class File {
    size_t depth_;
    size_t countRecursive_;
    std::string initPath_;
    std::string path_;
    std::string name_;
    std::string format_;
    std::vector<File> subFiles_;

    FileData data_;


public:
    File(  
        const size_t depth,
        const size_t countRecursive,
        const std::string& initPath,
        const std::string& path,
        const std::string& name,
        const std::string& format,
        const std::vector<File>& subFiles
        ):
        depth_(depth),
        countRecursive_(countRecursive),
        initPath_(initPath),
        path_(path),
        name_(name),
        format_(format),
        subFiles_(subFiles),
        data_()
    {}

    std::string getInitPath() const { return initPath_; }
    std::string getPath() const { return path_; }
    std::string getName() const { return name_; }
    std::string getFormat() const { return format_; }
    std::string getFile() const { return initPath_ + path_ + name_ + format_; }
    std::vector<File> getSubFiles() const { return subFiles_; }

    bool isCatalog() const { return !subFiles_.empty(); }
    size_t getDepth() const { return depth_; }
    size_t countSubFiles() const { return subFiles_.size(); }
    size_t countSubFilesRecursive() const { return countRecursive_; }

    void setData(const FileData& data) { data_ = data; }
    std::vector<std::string> getLibIncludes() const { return data_.getLibIncludes(); }
    std::vector<std::string> getProjIncludes() const { return data_.getProjIncludes(); }
};


