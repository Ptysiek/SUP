#pragma once

#include <string>
#include <vector>

#include "iSyntax.hpp"


class FileData {
    std::vector<std::string> libIncludes_;
    std::vector<std::string> projIncludes_;
    std::vector<std::shared_ptr<iSyntax>> data_;

public:
    FileData():
        libIncludes_(),
        projIncludes_(),
        data_()
    {}

    FileData(
        const std::vector<std::string>& libIncludes,
        const std::vector<std::string>& projIncludes,
        const std::vector<std::shared_ptr<iSyntax>>& data
        ):
        libIncludes_(libIncludes),
        projIncludes_(projIncludes),
        data_(data)
    {}

    std::vector<std::string> getLibIncludes() const { return libIncludes_; }
    std::vector<std::string> getProjIncludes() const { return projIncludes_; }
    std::vector<std::shared_ptr<iSyntax>> getData() const { return data_; }
};
