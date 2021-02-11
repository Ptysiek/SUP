#pragma once


#include "File.hpp"
#include "FileBuilder.hpp"
#include "FileIO.hpp"
#include "PathInitializer.hpp"
#include "ProjectTree.hpp"


class Program {

    const std::string targetPath_;
    ProjectTree data_;

public:
    explicit Program(const std::string& target):
        targetPath_(target),
        data_()
    {}

    void execute() {
        auto paths = FileIO::readPaths(targetPath_);
        
        ProcessPaths(paths);

    }

private:
    void ProcessPaths(const std::vector<std::string>& paths) {
        for (const auto& path : paths) {
            PathInitializer initializer(path);
            FileBuilder builder(initializer);
            data_.push(builder.getFile());
        }
    }
    std::vector<std::string> ReadSubdirectories(const std::string& path) {

    }

};

