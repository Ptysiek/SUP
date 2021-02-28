#include "plugins/catch.hpp"
#include "FileParserComments.ut.hpp"




TEST_CASE("FileParserComments: base operations", "[IsInsideString]") { 

    FileParserComments_UnitTest testObject;

    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    WHEN("Testing the IsInsideString()") {
        struct test {
            const std::string line_;
            const bool expectedValue_;

            std::string log() const {
                return 
                    "{ \"" + line_
                    + "\" == " + std::to_string(expectedValue_)
                    + " }";
            }
        };
        const std::initializer_list<test> tests = {
            { "", false },
            { "    abcd", false },
            { "abcd", false },
            { "  \"  a\"bcd", false },
            { "  \'  a\'bcd", false },
            { "  \" \"\" a\"bcd", false },
            { "  \' \'\' a\'bcd", false },
            { "  \" \'\' a\"bcd", false },
            { "  \' \"\" a\'bcd", false },
            { "  \" \'\" a\'bcd", false },
            { "  \' \"\' a\"bcd", false },

            { "  \"\"  a\'bcd", true },
            { "  \'\'  a\"bcd", true },

            { "  \"  a\'bcd", true },
            { "  \'  a\"bcd", true },
            { "  \"  abcd", true },
            { "  \'  abcd", true },
            { "\"\"  \"  abcd", true },
            { "\'\' ww  \'  abcd", true }
        };
        for (const auto& test : tests) {
            THEN(test.log()) {
                REQUIRE_NOTHROW(testObject.IsInsideString(test.line_));
                auto result = testObject.IsInsideString(test.line_);
                REQUIRE(result == test.expectedValue_);
            }
        }
    }
}


TEST_CASE("FileParserComments: static operations", "[RemoveOnelineComments], [RemoveMultilineComments]") {
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    /*
    WHEN("Testing the RemoveOnelineComments()") {
        struct test {
            const PathInitializer_UnitTest object_;
            const std::string expectedValue_;

            std::string log() const {
                return 
                    "{ \"" + object_.getTestValue()
                    + "\" == \"" + expectedValue_
                    + "\" }";
            }
        };
        const std::initializer_list<test> tests = {
        };

        for (const auto& test : tests) {
            THEN(test.log()) {
                REQUIRE_NOTHROW(test.object_.CutoutName());
                auto result = test.object_.CutoutName();
                REQUIRE(result == test.expectedValue_);
            }
        }
    }
*/
}




