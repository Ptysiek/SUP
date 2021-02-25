#pragma once

#include <string>
#include <vector>

#include "File.hpp"


class ParsedFile : public File {

    std::vector<std::string> data_;
    


public:
    explicit ParsedFile(const File& base, const std::vector<std::string>& data):
        File(base),
        data_(data)
    {}



};

