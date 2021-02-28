#include "FileParserComments.hpp"


class FileParserComments_UnitTest : FileParserComments {
public:
    FileParserComments_UnitTest() {}

    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    bool IsInsideString(const Line& line) {
        return FileParserComments::IsInsideString(line);
    }
    bool IsAlreadyCommentedByOneline(const Line& subline) {
        return FileParserComments::IsAlreadyCommentedByOneline(subline);
    }
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    Line RemoveOnelineComments(const Line& line) { 
        return FileParserComments::RemoveOnelineComments(line);
    }
    Data RemoveAllOnelineComments(const Data& data) {
        return FileParserComments::RemoveAllOnelineComments(data);
    }
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    Line Multiline_ClearLine(const Line& line, bool& isCommented) {
        return FileParserComments::Multiline_ClearLine(line, isCommented);
    }
};




