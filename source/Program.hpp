#pragma once

#include "File.hpp"
#include "FileBuilder.hpp"
#include "ProjectTreeBuilder.hpp"


class Program {
    const std::string targetPath_;
    ProjectTree data_;

public:
    explicit Program(const std::string& target):
        targetPath_(target),
        data_()
    {}

    void execute() {
        ProjectTreeBuilder builder(targetPath_);
        data_ = builder.getProduct();
    }

private:
};

