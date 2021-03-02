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

    static std::string to_string(const std::vector<std::string>& data2) {
        std::stringstream result;       
        auto data = removeEmptyLines(data2);
        std::for_each(data.begin(), data.end(), [&](const auto& line){result << removeWhitespaces(line) << "\n";});
        return result.str();
    }

    static std::string AppendConditionalSlash(std::string str) {
        if (!str.empty()) {
            str += (str.at(str.size()-1) == '/')? "" : "/";  
        }
        return str;
    }

    static std::string removeWhitespaces(const std::string& data) {
        std::string result = data;
        result = RemoveSpecialChars(result);
        result = RemoveFromBegin(result);
        result = RemoveFromEnd(result);
        result = RemoveAdjacentSpaces(result);
        return result;
    }

    static std::vector<std::string> removeEmptyLines(const std::vector<std::string>& data) {
        std::vector<std::string> result;
        result.reserve(data.size());

        for (auto record : data) {
            record = removeWhitespaces(record);
            if (!record.empty()) {
                result.push_back(record);
            }
        }
        return result;
    }


private:
    static std::string RemoveSpecialChars(const std::string& data) {
        std::string result = data;
        std::for_each(begin(result), end(result), 
            [](auto& ch){ ch = (ch == '\n' || ch == '\t')? ' ' : ch; });
        return result;
    }
    static std::string RemoveFromBegin(const std::string& data) {
        size_t i = 0;
        for ( ; i < data.size(); ++i) {
            if (data[i] != ' ') {
                break;
            }
        }
        return data.substr(i);
    }
    static std::string RemoveFromEnd(const std::string& data) {
        int i = static_cast<int>(data.size()) - 1;
        for ( ; i >= 0; --i) {
            if (data[i] != ' ') {
                break;
            }
        }
        return data.substr(0, i+1);
    }
    static std::string RemoveAdjacentSpaces(const std::string& data) {
        std::stringstream result;
        bool foundSpace = false;
        for (size_t i = 0; i < data.size(); ++i) {
            if (!foundSpace) {
                result << data[i];
                foundSpace = (data[i] == ' ');
                continue;
            }
            foundSpace = (data[i] == ' ');
            if (!foundSpace) {
                result << data[i];
            }
        }
        return result.str();
    }
};
} // namespace Tools



