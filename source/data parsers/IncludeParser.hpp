#pragma once

#include "../DataStructures"


namespace DataParsers {
class IncludeParser {
    using Converter = Tools::Converter;
    using Data = DataStructures::Data;
    using Line = DataStructures::Line;
    
    Data data_;
    Data libIncludes_;
    Data projIncludes_;


public:
    IncludeParser(const Data& data):
        data_(data),
        libIncludes_(),
        projIncludes_()
    {
        BuildIncludes();
    }

    Data getLibIncludes() const { return libIncludes_; }
    Data getProjIncludes() const { return projIncludes_; }
    Data getData() const { return data_; }


protected:
    void BuildIncludes() {
        auto includes = CutoutIncludes();

        for (auto str : includes) {
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
        std::sort(libIncludes_.begin(), libIncludes_.end());
        std::sort(projIncludes_.begin(), projIncludes_.end());
    }

    Data CutoutIncludes() {
        Data includes;
        for (auto& line : data_) {
            size_t i = line.find("#include");
            
            if (i == std::string::npos) {
                continue;
            }
            std::string str; 
            str = line.substr(i + 8);
            str = Converter::removeWhitespaces(str);

            includes.push_back(str);
            line = "";
        }
        return includes;
    }
};
} // namespace DataParsers



