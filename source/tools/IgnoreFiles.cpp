#include <string>
#include <vector>

#include "IgnoreFiles.hpp"


namespace Tools {
    const std::string IgnoreFiles::filename_ = ".supignore";

    const std::set<std::string> IgnoreFiles::formatIgnores_ {
        ".ut.cpp",
        ".ut.hpp"
    };
    const std::set<std::string> IgnoreFiles::alwaysIgnores_ {
        "\n",
        "",
        ".",
        "..",
        "./",
        "../"
    };
    std::set<std::string> IgnoreFiles::defaultIgnores_ {
        ".git",
        ".gitignore",
        ".notes",
        ".sup",
        "notes",
        "build",
        "plugins",
        "tags",
        "README.md",
        "CMakeLists.txt"
    };
} // namespace Tools



