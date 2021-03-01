#pragma once

#include "DataStructures"
#include "Tools"

#include "FileParserComments.hpp"
#include "FileParserSyntax.hpp"


class FileParser {
    using Data = DataStructures::Data;
    const std::string initPath_;
    const File rawFile_;
    const ParsedFile product_;


public:
    FileParser(const std::string& initPath, const File& file):
        initPath_(initPath),
        rawFile_(file),
        product_(BuildProduct())
    {}

    ParsedFile getProduct() const { return product_; }


private:
    ParsedFile BuildProduct() const {
        auto data = Tools::FileIO::readFile(initPath_ + rawFile_.getFile());
        data = FileParserComments::modifyData(data);
        auto includes = CutoutIncludes(data);
        auto tagMap = FileParserSyntax::tagData(data);

        return ParsedFile(rawFile_, data, includes);
    }

    std::vector<std::string> CutoutIncludes(Data& data) const {
        std::vector<std::string> includes;
        for (auto& line : data) {
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

