#pragma once

#include <algorithm>
#include <set>
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

};
} // namespace Tools



