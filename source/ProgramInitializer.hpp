#pragma once

#include <string>

#include "Tools"

/* TODO:
    - create flag support  -md -markdown -txt -text
*/


class ProgramInitializer {
    using IgnoreFiles = Tools::IgnoreFiles;
    using Converter = Tools::Converter;
    const std::string path_;


public:
    explicit ProgramInitializer(const int& argc, const char* const * const argv):
        path_(GenPath(argc, argv))
    {}

    std::string getPath() const { return path_; }
    std::string getDefaultPath() const { return "../"; }


private:
    std::string GenPath(const int& argc, const char* const * const argv) const {
        if (argc > 1) {
            return Converter::AppendConditionalSlash(argv[1]);
        }
        return getDefaultPath();
    }
};




