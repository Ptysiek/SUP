#pragma once

#include "File.hpp"
#include "ParsedFile.hpp"
#include "Tools"


class FileParser {
    const std::string initPath_;
    const File rawFile_;
    const ParsedFile product_;


public:
    FileParser(const std::string& initPath, const File& file):
        initPath_(initPath),
        rawFile_(file),
        product_(BuildProduct())
    {}


private:
    ParsedFile BuildProduct() const {
        auto data = Tools::FileIO::readFile(initPath_+rawFile_.getFile());
        
        ParsedFile result(rawFile_, data);
        return result;
    }


};

