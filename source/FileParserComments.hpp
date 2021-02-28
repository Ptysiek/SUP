#pragma once

#include "DataStructures"
#include "Tools"


class FileParserComments {
    using Data = DataStructures::Data;
    FileParserComments() {}


public:
    static Data modifyData(Data data) {
        RemoveOnelineComments(data);
        RemoveMultilineComments(data);
        return data;
    }


private:
    static Data RemoveOnelineComments(Data data) {
        for (auto& line : data) {
            auto i = line.find("//");
            if (i != std::string::npos) {
                line = line.substr(0, i);
            }
        }
        return data;
    }

    static Data RemoveMultilineComments(Data data) {
        /*TODO:
         * Simplify.
         * sift string data ex.("abcd // cde";  // comment)
        */
        bool isCommented = false;

        for (auto& line : data) {
            if (isCommented) {
                auto end = line.find("*/");
                if (end != std::string::npos) {
                    line = line.substr(end + 2);
                    isCommented = false;
                }
                else {
                    line = "";
                }
            }
            auto begin = line.find("/*");
            if (begin != std::string::npos) {
                auto end = line.find("*/", begin);
                if (end != std::string::npos) {
                    std::string tmp = line.substr(end + 2);
                    line = line.substr(0, begin);
                    line += ' ' + tmp;
                }
                else {
                    line = line.substr(0, begin);
                    isCommented = true;
                }
            }
        }
        return data;
    }
};

