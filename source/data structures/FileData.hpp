#pragma once

#include <string>
#include <vector>


class FileData {
    std::vector<std::string> libIncludes_;
    std::vector<std::string> projIncludes_;
    

public:
    FileData():
        libIncludes_(),
        projIncludes_()
    {}

    FileData(
        const std::vector<std::string>& libIncludes,
        const std::vector<std::string>& projIncludes
        ):
        libIncludes_(libIncludes),
        projIncludes_(projIncludes)
    {}

    std::vector<std::string> getLibIncludes() const { return libIncludes_; }
    std::vector<std::string> getProjIncludes() const { return projIncludes_; }


private:

};
