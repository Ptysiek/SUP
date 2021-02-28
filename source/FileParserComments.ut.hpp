#include "FileParserComments.hpp"


class FileParserComments_UnitTest : FileParserComments {
public:
    FileParserComments_UnitTest() {}

    bool IsInsideString(const Line& line) {
        return FileParserComments::IsInsideString(line);
    }
    Line RemoveOnelineComments(const Line& line) { 
        return FileParserComments::RemoveOnelineComments(line);
    }


};
