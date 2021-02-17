#pragma once

#include <exception>
#include <string>
//#include 


class PathInitializer {
    size_t index_;
    //const std::string init_;
    const std::string path_;
    const std::string name_;
    const std::string format_;


public:
    PathInitializer(const int& argc, const char* const * const argv):
        index_(),
        path_(GenPath(argc, argv)),
        name_(),
        format_()
    { }

    PathInitializer(const std::string& path, const std::string& fullName):
        index_(0),
        path_(GenConditionalSlash(path)),
        name_(GenName(fullName)),
        format_(GenFormat(fullName))
    { }

    std::string getPath() const { return path_; }
    std::string getName() const { return name_; }
    std::string getFormat() const { return format_; }
    std::string getDefaultPath() const { return "../"; }
    std::string getFullName() const { return (name_ + format_); }
    std::string getFullPath() const { return (path_ + getFullName()); }
    //std::string getRelativePath() const { return

private:
    std::string GenPath(const int& argc, const char* const * const argv) const {
        if (argc > 1) {
            return GenConditionalSlash(argv[1]);
        }
        return getDefaultPath();
    }

    std::string GenName(const std::string& fullName) {
        if (fullName == "./" || fullName == "../") {
            return fullName;
        }
        std::string fileName = "";
        const size_t size = fullName.size();
        
        for ( ; index_ < size; ++index_) {
            if (fullName[index_] == '.') {
                if (index_ != 0) {
                    break;
                }
            }
            fileName += fullName[index_];
        }
        return fileName;
    }

    std::string GenFormat(const std::string& fullName) {
        if (fullName == "./" || fullName == "../") {
            return "";
        }
        auto index = fullName.find('.', 1);
        std::string fileFormat;// = "  ";
        fileFormat.insert(fileFormat.begin(), fullName.begin()+index, fullName.end());
        return fileFormat;
    }

    std::string GenConditionalSlash(std::string str) const {
        if (!str.empty()) {
            str += (str.at(str.size()-1) == '/')? "" : "/";  
        }
        return str;
    }
};

