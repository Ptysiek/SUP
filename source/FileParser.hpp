#pragma once

//#include "File.hpp"
//#include "ParsedFile.hpp"
#include "DataStructures"
#include "Tools"


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
        auto data = Tools::FileIO::readFile(initPath_+rawFile_.getFile());
        RemoveOnelineComments(data);
        RemoveMultilineComments(data);
        auto includes = CutoutIncludes(data);

        return ParsedFile(rawFile_, data, includes);
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
        /*TODO:
         * Simplify.
         * sift string data ex.("abcd // cde";  // comment)
        */
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
        }
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

