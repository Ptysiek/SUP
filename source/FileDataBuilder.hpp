#pragma once

#include "Tools"
#include "DataStructures"
#include "DataParsers"
using namespace DataParsers;


class FileDataBuilder {
    using FileIO = Tools::FileIO;
    using Converter = Tools::Converter;
    using Data = DataStructures::Data;

    bool productExist_;
    Data rawData_;
    const File& fileHeader_;    
    const FileData product_;

    std::vector<std::string> libIncludes_;
    std::vector<std::string> projIncludes_;


public:
    FileDataBuilder(const File& file):
        productExist_(false),
        rawData_(),
        fileHeader_(file),
        product_(BuildProduct()),
        libIncludes_(),
        projIncludes_()
    {}

    bool dataExist() const { return productExist_; }
    FileData getProduct() const { return product_; }


private:
    FileData BuildProduct() {
        if (fileHeader_.isCatalog()) {
            return BuildEmptyData();
        }
        rawData_ = FileIO::readFile(fileHeader_.getFile());
        rawData_ = PrepareData(rawData_);

        SyntaxParser synParser(rawData_);
        auto syntaxData = synParser.getProduct();
 
        productExist_ = true;
        return {libIncludes_, projIncludes_, syntaxData};
    }


    FileData BuildEmptyData() {
        productExist_ = false;
        return FileData();
    }

    Data PrepareData(Data rawData) {
        rawData = CommentParser::removeComments(rawData);

        IncludeParser incParser(rawData);
        libIncludes_ = incParser.getLibIncludes();
        projIncludes_ =  incParser.getProjIncludes();
        rawData = incParser.getData();
        
        rawData = DirectiveParser::removeDirectives(rawData);

        rawData = Converter::removeWhitespaces(rawData);
        rawData = Converter::removeEmptyLines(rawData);
        return rawData;
    }
};

