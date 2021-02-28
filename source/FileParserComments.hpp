#pragma once

#include <exception>

#include "DataStructures"
//#include "Tools"


class FileParserComments {
    using Data = DataStructures::Data;
    using Line = DataStructures::Line;

protected:
    FileParserComments() {}


public:
    static Data modifyData(Data data) {
        RemoveAllOnelineComments(data);
        RemoveMultilineComments(data);
        return data;
    }


protected:
    static Data RemoveAllOnelineComments(Data data) {
        for (auto& line : data) {
            line = RemoveOnelineComments(line);
        }
        return data;
    }

    static Line RemoveOnelineComments(const Line& line) {
        auto i = line.find("//");
        if (i == std::string::npos) {
            return line;
        }
        if (IsInsideString(line.substr(0, i))) {
            return line;
        }
        return line.substr(0, i);
    }

    static bool IsInsideString(const Line& subline) {
        auto count_a = std::count(subline.begin(), subline.end(), '\"');
        auto count_b = std::count(subline.begin(), subline.end(), '\'');
        return (count_a % 2) || (count_b % 2);
    }


    static Data RemoveMultilineComments(Data data) {
        /*TODO:
         * sift string data ex.("abcd // cde";  // comment)
        */
        bool isCommented = false;

        for (auto& line : data) {
            if (isCommented) {
                ClearLine(line, isCommented);
            }
            auto begin = line.find("/*");
            if (begin != std::string::npos) {
                FindClosing(line, isCommented, begin);
            }
        }
        return data;
    }
    
    static Line ClearLine(Line line, bool& isCommented) {
        auto end = line.find("*/");
        if (end != std::string::npos) {
            isCommented = false;
            return line.substr(end + 2);
        }
        return "";
    }

    static Line FindClosing(Line line, bool& isCommented, const size_t begin) {
        auto end = line.find("*/", begin);
        if (end != std::string::npos) {
            std::string tmp = line.substr(end + 2);
            return line.substr(0, begin) + " " + tmp;
        }
        isCommented = true;
        return line.substr(0, begin);
    }

};

