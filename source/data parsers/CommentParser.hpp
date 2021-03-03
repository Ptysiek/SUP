#pragma once


/* TODO:
- fix multiline comments
ex:   abcd  *//* */ /* *** */  /* */ /* abcdc */


class CommentParser {
protected:
 
    using Data = DataStructures::Data;
    using Line = DataStructures::Line;

    CommentParser() {}


public:
    static Data removeComments(Data data) {
        RemoveAllOnelineComments(data);
        RemoveMultilineComments(data);
        return data;
    }


protected:
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
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

    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    static Data RemoveMultilineComments(Data data) {
        bool isCommented = false;
        for (auto& line : data) {
            if (isCommented) {
                Multiline_ClearLine(line, isCommented);
            }
            auto begin = line.find("/*");
            if (begin != std::string::npos) {
                Multiline_FindClosing(line, isCommented, begin);
            }
        }
        return data;
    }
    static Line Multiline_ClearLine(Line line, bool& isCommented) {
        auto end = line.find("*/");
        
        if (end == std::string::npos) {
            return "";
        }
        if (IsAlreadyCommentedByOneline(line.substr(0, end))) {
            return "";
        }
        if (IsInsideString(line.substr(0, end))) {
            return "";
        }
        isCommented = false;
        return line.substr(end + 2);
    }
    static Line Multiline_FindClosing(Line line, bool& isCommented, const size_t begin) {
        auto end = line.find("*/", begin);
        
        if (end != std::string::npos) {
            std::string tmp = line.substr(end + 2);
            return line.substr(0, begin) + " " + tmp;
        }
        isCommented = true;
        return line.substr(0, begin);
    }

    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    static bool IsInsideString(const Line& subline) {
        auto count_a = std::count(subline.begin(), subline.end(), '\"');
        auto count_b = std::count(subline.begin(), subline.end(), '\'');
        return (count_a % 2) || (count_b % 2);
    }

    static bool IsAlreadyCommentedByOneline(const Line& subline) {
        return (subline.find("//") != std::string::npos);
    }
};



