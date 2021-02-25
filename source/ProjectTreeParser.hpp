#pragma once

#include <algorithm>
#include <string>

#include "Tools"
#include "PathInitializer.hpp"


using RawProjectTree = std::vector<File>;
using ParsedProjectTree = std::vector<ParsedFile>;

class ProjectTreeParser {
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
    ParsedProjectTree BuildProduct() {
        return ParsedProjectTree();
    }
};



