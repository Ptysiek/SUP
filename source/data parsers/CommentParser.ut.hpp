#include "CommentParser.hpp"


class CommentParser_UnitTest : CommentParser {
public:
    CommentParser_UnitTest() {}

    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    bool IsInsideString(const Line& line) {
        return CommentParser::IsInsideString(line);
    }
    bool IsAlreadyCommentedByOneline(const Line& subline) {
        return CommentParser::IsAlreadyCommentedByOneline(subline);
    }
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    Line RemoveOnelineComments(const Line& line) { 
        return CommentParser::RemoveOnelineComments(line);
    }
    Data RemoveAllOnelineComments(const Data& data) {
        return CommentParser::RemoveAllOnelineComments(data);
    }
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    Line Multiline_ClearLine(const Line& line, bool& isCommented) {
        return CommentParser::Multiline_ClearLine(line, isCommented);
    }
};




