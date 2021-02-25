#pragma once

#include <sstream>
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

    std::string getData() const {
        std::stringstream result;       
        std::for_each(data_.begin(), data_.end(), [&](const auto& line){result << line << "\n";});
        return result.str();
    }


};

