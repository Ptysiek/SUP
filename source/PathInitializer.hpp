#pragma once

#include <string>

#include "Tools"


class PathInitializer {
    const std::string path_;
    const std::string name_;
    const std::string format_;


public:
    explicit PathInitializer(const int& argc, const char* const * const argv):
        path_(GenPath(argc, argv)),
        name_(),
        format_()
    {}

    explicit PathInitializer(const std::string& path, const std::string& fullName):
        path_(AppendConditionalSlash(path)),
        name_(CutoutName(fullName)),
        format_(CutoutFormat(fullName))
    {}

    std::string getPath() const { return path_; }
    std::string getName() const { return name_; }
    std::string getFormat() const { return format_; }
    std::string getDefaultPath() const { return "../"; }


private:
    std::string GenPath(const int& argc, const char* const * const argv) const {
        if (argc > 1) {
            return AppendConditionalSlash(argv[1]);
        }
        return getDefaultPath();
    }


protected:
    static std::string CutoutName(const std::string& str) {
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

    static std::string CutoutFormat(const std::string& str) {
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

    static std::string AppendConditionalSlash(std::string str) {
        if (!str.empty()) {
            str += (str.at(str.size()-1) == '/')? "" : "/";  
        }
        return str;
    }
};




