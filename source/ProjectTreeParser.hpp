#pragma once

#include <algorithm>
#include <string>

#include "Tools"
#include "FileParser.hpp"
//#include "PathInitializer.hpp"



class ProjectTreeParser {

/*
    using RawProjectTree = DataStructures::ProjectTree;  //std::vector<File>;
    using ParsedProjectTree = DataStructures::ParsedProjectTree;  //std::vector<ParsedFile>;
    const std::string initPath_;
    const RawProjectTree rawData_;
    const ParsedProjectTree product_;

public:
    explicit ProjectTreeParser(const std::string& initPath, const RawProjectTree& rawData):
        initPath_(initPath),
        rawData_(rawData),
        product_(BuildProduct())
    {}

    ParsedProjectTree getProduct() const { return product_; }
    

private:
    ParsedProjectTree BuildProduct() const {
        ParsedProjectTree result;
        result.reserve(rawData_.size());

        for (const auto& file : rawData_) {
            FileParser parser(initPath_, file);
            result.push_back(parser.getProduct());
        }

        return result;
    }
    */
};



