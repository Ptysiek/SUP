#pragma once

#include <sstream>

#include "Tools"
#include "DataStructures"


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
        
        result << "\n\n";
        result << BuildHeader();
        result << "\n\n";
        result << BuildTableOfContents();
        
        for (const auto& file : data_) {
            if (file.isCatalog()) {
                continue;
            }
            result << "\n\n\n############################################################################  "; 
            result << file.getFile();

            result << "\n";
            result << Tools::Converter::to_string(file.getData().getLibIncludes()) << "\n";
            result << Tools::Converter::to_string(file.getData().getProjIncludes()) << "\n";
            result << "\n\n\n############################################################################\n"; 
            
            for (const auto& ptr : file.getData().getData()) {
                result << "[" << ptr->getResult() << "]\n";

            }

            result << "\n\n\n############################################################################\n"; 
        }
        return result.str();
    }

private:
    std::string BuildTableOfContents() {
        std::stringstream result;       

        result << "### Table Of Contents: #####################################################\n"; 
        result << "############################################################################\n"; 
        for (size_t f = 1; f < data_.size(); ++f) {
            const auto& file = data_[f];

            if (file.isCatalog()) {
                result << "\n";
            }
            for (size_t i = 0; i < file.getDepth(); ++i) {
                result << "\t";
            }
            if (file.isCatalog()) {
                result << "[" << file.getPath() << file.getName() << "]\n";
            }
            else {
                result << file.getName() << file.getFormat() << "\n"; 
            }
        }
        return result.str();
    }
    
    std::string BuildHeader() {
        return "Author of SUP-SeeYourPoint: Kacu Kacper Kaleta [https://github.com/Ptysiek]\n";
    }


};

