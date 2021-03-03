#pragma once

#include "../DataStructures"


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
        std::sort(libIncludes_.begin(), libIncludes_.end());
        std::sort(projIncludes_.begin(), projIncludes_.end());
    }

    Data CutoutIncludes() {
        Data includes;
        for (auto& line : data_) {
            if (Tools::Converter::removeWhitespaces(line)[0] != '#') {
                continue;
            }

            if (line.find("#include") != std::string::npos) {
                includes.push_back(line.substr(8));
                line = "";
            }
        }
        return includes;
    }
};




