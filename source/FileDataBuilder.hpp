#pragma once

#include "Tools"
#include "DataStructures"
#include "data parsers/CommentParser.hpp"


class FileDataBuilder {
    using Data = DataStructures::Data;
    
    bool productExist_;
    Data rawData_;
    const File& fileHeader_;    
    const FileData product_;


public:
    FileDataBuilder(const File& file):
        productExist_(false),
        rawData_(),
        fileHeader_(file),
        product_(BuildProduct())
    {}

    bool dataExist() const { return productExist_; }
    FileData getProduct() const { return product_; }

    

private:
    FileData BuildProduct() {
        if (fileHeader_.isCatalog()) {
            return BuildEmptyData();
        }
        rawData_ = Tools::FileIO::readFile(fileHeader_.getFile());

        //data = FileParserComments::modifyData(data);
        //auto includes = CutoutIncludes(data);
 
 
 
 //       SyntaxedData syntaxedData_;
   //     syntaxedData = FileParserSyntax::generateSyntax(data);

      //  return ParsedFile(rawFile_, data, syntaxedData, includes);
        //return {data, includes};
        productExist_ = true;
        return BuildEmptyData();
    }

    FileData BuildEmptyData() {
        productExist_ = false;
        return FileData();
    }

/*
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
    */
};

