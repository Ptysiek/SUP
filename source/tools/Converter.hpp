#pragma once

#include <algorithm>
#include <set>
#include <sstream>
#include <vector>


namespace Tools {
class Converter {
public:    
    template <class T>
    static std::set<T> to_set(const std::vector<T>& data) {
        return std::set<T>(data.begin(), data.end());
    }

    static std::string to_fileData(const std::set<std::string>& data) {
        std::string result;
        std::for_each (data.begin(), data.end(), [&](const auto& val){result += val + '\n';});
        return result;
    }

    static std::string to_string(const std::vector<std::string>& data) {
        std::stringstream result;       
        std::for_each(data.begin(), data.end(), [&](const auto& line){result << line << "\n";});
        return result.str();
    }

    static std::string removeWhitespaces(const std::string& data) {
        std::stringstream result;       
        for (const auto& character : data) {
            if (character == ' ' || character == '\t' || character == '\n') {
                continue;
            }
            result << character;
        }
        return result.str();
    }

};
} // namespace Tools



