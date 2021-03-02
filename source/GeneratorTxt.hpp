#pragma once

#include <sstream>

#include "data structures/File.hpp"
#include "Tools"


class GeneratorTxt {
    const std::string targetPath_;
    std::vector<File> data_;

public:
    explicit GeneratorTxt(const std::string& targetPath, const std::vector<File>& data):
        targetPath_(targetPath),
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
            result << Tools::Converter::to_string(file.getData().getLibIncludes()) << "\n";
            result << Tools::Converter::to_string(file.getData().getProjIncludes()) << "\n";
            result << "\n\n\n############################################################################\n"; 
        }
        return result.str();
    }
};

