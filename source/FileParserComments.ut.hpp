#include "FileParserComments.hpp"


class FileParserComments_UnitTest : FileParserComments {
public:
    FileParserComments_UnitTest() {}

    bool IsInsideString(const std::string& line) {
        return FileParserComments::IsInsideString(line);
    }  
};

