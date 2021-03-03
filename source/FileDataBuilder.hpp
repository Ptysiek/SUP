#pragma once

#include "Tools"
#include "DataStructures"
#include "data parsers/CommentParser.hpp"
#include "data parsers/IncludeParser.hpp"
#include "data parsers/SyntaxParser.hpp"


class FileDataBuilder {
    using Data = DataStructures::Data;
    using Converter = Tools::Converter;

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
 
        rawData_ = CommentParser::removeComments(rawData_);

        IncludeParser incParser(rawData_);
        auto libs = incParser.getLibIncludes();
        auto projs = incParser.getProjIncludes();
        rawData_ = incParser.getData();

        rawData_ = Converter::removeWhitespaces(rawData_);
        rawData_ = Converter::removeEmptyLines(rawData_);

        SyntaxParser synParser(rawData_);
        auto syntaxData = synParser.getProduct();
        rawData_ = synParser.getData();
 
        productExist_ = true;
        return {libs, projs, syntaxData};
        return FileData();
    }


    FileData BuildEmptyData() {
        productExist_ = false;
        return FileData();
    }

};

