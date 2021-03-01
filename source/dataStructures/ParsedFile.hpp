#pragma once

#include <algorithm>
#include <string>
#include <vector>

//#include "../DataStructures"
#include "FileHeader.hpp"
#include "../Tools"
#include "BaseStructures"

class ParsedFile : public FileHeader {
    using Converter = Tools::Converter;
    using Data = BaseStructures::Data; // std::vector<std::string>;
 //   using SyntaxedData = DataStructures::SyntaxedData;
    Data data_;
 //   SyntaxedData syntaxedData_;
    Data libIncludes_;
    Data projIncludes_;
    


public:
    explicit ParsedFile(const FileHeader& base, const Data& data,
        /* const SyntaxedData& syntaxedData,*/ const Data& includes):
        FileHeader(base),
        data_(data),
        //syntaxedData_(syntaxedData),
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

