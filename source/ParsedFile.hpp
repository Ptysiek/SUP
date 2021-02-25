#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "File.hpp"
#include "Tools"


class ParsedFile : public File {
    using DataConteiner = std::vector<std::string>;
    DataConteiner data_;
    DataConteiner libIncludes_;
    DataConteiner projIncludes_;
    


public:
    explicit ParsedFile(const File& base, const DataConteiner& data, const DataConteiner& includes):
        File(base),
        data_(data),
        libIncludes_(),
        projIncludes_()
    {
        BuildIncludes(includes);    
    }

    std::string getData() const { return Tools::Converter::to_string(data_); } 

    std::vector<std::string> getLibIncludes() const { return libIncludes_; }
    
    std::vector<std::string> getProjIncludes() const { return projIncludes_; }


private:
    void BuildIncludes(const DataConteiner& includes) {
        for (auto str : includes) {
            str = Tools::Converter::removeWhitespaces(str);
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
    }
};

