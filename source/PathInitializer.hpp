#pragma once

#include <exception>
#include <string>


class PathInitializer {
    size_t index_;
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

    PathInitializer(const std::string path):
        index_(0),
        path_(path),
        name_(GenName()),
        format_(GenFormat())
    { }

    std::string getPath() const { return path_; }
    std::string getName() const { return name_; }
    std::string getFormat() const { return format_; }
    std::string getDefaultPath() const { return "../"; }


private:
    std::string GenPath(const int& argc, const char* const * const argv) const {
        if (argc > 1) {
            return GenConditionalSlash(argv[1]);
        }
        return getDefaultPath();
    }

    std::string GenName() {
        std::string fileName = "";
        const size_t size = path_.size();
        
        for ( ; index_ < size; ++index_) {
            if (path_[index_] == '.') {
                break;
            }
            fileName += path_[index_];
        }
        return fileName;
    }

    std::string GenFormat() {
        std::string fileFormat = "";
        const size_t size = path_.size();

        for ( ; index_ < size; ++index_) {
            fileFormat += path_[index_];
        }
        return fileFormat;
    }

    std::string GenConditionalSlash(std::string str) const {
        str += (str.at(str.size()-1) == '/')? "" : "/";  
        return str;
    }
};

