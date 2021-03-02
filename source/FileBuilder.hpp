#pragma once

#include <string>

#include "Tools"
#include "dataStructures/File.hpp"


class FileBuilder {
    using IgnoreFiles = Tools::IgnoreFiles;
    const std::string initPath_;
    const std::string path_;
    const std::string name_;
    const std::string format_;

    const File product_;

    
public:
    explicit FileBuilder(
        const std::string& initPath,
        const std::string& path, 
        const std::string& fullName, 
        const std::vector<File>& subfiles, 
        const int depth):
        initPath_(AppendConditionalSlash(initPath)),
        path_(AppendConditionalSlash(path)),
        name_(CutoutName(fullName)),
        format_(CutoutFormat(fullName)),
        product_(BuildProduct(subfiles, depth))
    {}

    File getProduct() const { return product_; }

    static File buildRoot(const std::string& initPath, const std::vector<File>& subFiles) {
        return {0, "" , "", initPath, "", subFiles};
    }






protected:
    File BuildProduct(const std::vector<File>& subFiles, int depth) {
        return {depth, initPath_, path_, name_, format_, subFiles};
        //return File(initPath_, name_, path_, format_, subFiles, depth);
    }

    std::string CutoutName(const std::string& str) const {
        if (Tools::IgnoreFiles::isIgnored(str)) {
            return str;
        }
        auto index = str.find('.', 1);
        if (index == std::string::npos) {
            return str;
        }
        index = str.size() - index;
        std::string result;
        result.insert(result.begin(), str.begin(), str.end()-index);
        return result;
    }

    std::string CutoutFormat(const std::string& str) const {
        if (Tools::IgnoreFiles::isIgnored(str)) {
            return "";
        }
        auto index = str.find('.', 1);
        if (index == std::string::npos) {
            return "";
        }
        std::string result;
        result.insert(result.begin(), str.begin()+index, str.end());
        return result;
    }

    std::string AppendConditionalSlash(std::string str) const {
        if (!str.empty()) {
            str += (str.at(str.size()-1) == '/')? "" : "/";  
        }
        return str;
    }
};




