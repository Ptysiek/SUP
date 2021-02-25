#pragma once

#include <sstream>

#include "Tools"


class GeneratorTxt {
    using ParsedProjectTree = std::vector<ParsedFile>;
    const std::string initPath_;
    const ParsedProjectTree data_;


public:
    explicit GeneratorTxt(const std::string& initPath, const ParsedProjectTree& data):
        initPath_(initPath),
        data_(data)
    {}


    std::string buildFile() {
        std::stringstream result;       

        for (const auto& file : data_) {
            result << file.getPath() << "  "; 
            result << file.getName() << "  "; 
            result << file.getFormat() << "\t\t\t"; 
            result << std::to_string(file.getSubFiles().size()) << "\n"; 
        }

        for (const auto& file : data_) {
            result << "\n\n\n############################################################################  "; 
            result << file.getFile() << "\n";
            result << Tools::Converter::to_string(file.getLibIncludes()) << "\n";
            result << Tools::Converter::to_string(file.getProjIncludes()) << "\n";
            result << "\n\n\n############################################################################  "; 
            result << file.getData();
        }

        return result.str();
    }
    

};

