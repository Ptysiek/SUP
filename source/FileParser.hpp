#pragma once

#include "File.hpp"
#include "ParsedFile.hpp"
#include "Tools"


class FileParser {
    using Data = std::vector<std::string>;
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
        auto data = Tools::FileIO::readFile(initPath_+rawFile_.getFile());
        RemoveOnelineComments(data);
        RemoveMultilineComments(data);

        ParsedFile result(rawFile_, data);
        return result;
    }

    void RemoveOnelineComments(Data& data) const {
        for (auto& line : data) {
            auto i = line.find("//");
            if (i != std::string::npos) {
                line = line.substr(0, i);
            }
        }
    }

    void RemoveMultilineComments(Data& data) const {
        bool isCommented = false;

        for (auto& line : data) {
            if (isCommented) {
                auto end = line.find("*/");
                if (end != std::string::npos) {
                    line = line.substr(end + 2);
                    isCommented = false;
                }
                else {
                    line = "";
                }
            }
            //else {
                auto begin = line.find("/*");
                if (begin != std::string::npos) {
                    auto end = line.find("*/", begin);
                    if (end != std::string::npos) {
                        std::string tmp = line.substr(end + 2);
                        line = line.substr(0, begin);
                        line += ' ' + tmp;
                    }
                    else {
                        line = line.substr(0, begin);
                        isCommented = true;
                    }
                }
            //}
        }
    }
};

