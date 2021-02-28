#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "File.hpp"
#include "../Tools"
#include "BaseStructures"


class ParsedFile : public File {
    using Converter = Tools::Converter;
    using Data = BaseStructures::Data; // std::vector<std::string>;
    Data data_;
    Data libIncludes_;
    Data projIncludes_;
    


public:
    explicit ParsedFile(const File& base, const Data& data, const Data& includes):
        File(base),
        data_(data),
        libIncludes_(),
        projIncludes_()
    {
        BuildIncludes(includes);    
    }

    std::string getData() const { return Converter::to_string(data_); } 

    std::vector<std::string> getLibIncludes() const { return libIncludes_; }
    
    std::vector<std::string> getProjIncludes() const { return projIncludes_; }


private:
    void BuildIncludes(const Data& includes) {
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
    }
};

