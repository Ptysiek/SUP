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
/*    void BuildIncludes(const Data& includes) {
        for (auto str : includes) {
            str = Converter::removeWhitespaces(str);
            if (str.at(0) == '<') {
                libIncludes_.push_back(str.substr(1, str.length() - 2));
            }
            else if (str.at(0) == '\"') {
                projIncludes_.push_back(str.substr(1, str.length() - 2));
            }
            else {
                throw std::logic_error("ParsedFile::BuildIncludes():  wrong syntax \"" + str + "\"");
            }
        }
    }*/
};

