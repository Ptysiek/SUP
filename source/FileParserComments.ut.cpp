#include "plugins/catch.hpp"
#include "FileParserComments.ut.hpp"

#include <algorithm>
#include <numeric>


FileParserComments_UnitTest testObject;

TEST_CASE("FileParserComments: base operations", "[IsInsideString], [IsAlreadyCommentedByOneline]") { 
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
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    WHEN("Testing the IsInsideString()") {
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
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    WHEN("Testing the IsAlreadyCommentedByOneline()") {
        const std::initializer_list<test> tests = {
            { "", false },
            { "/", false },
            { "    abcd", false },
            { "abcd", false },
            
            { "//", true },
            { "    abcd//", true },
            { "    ab//cd", true },
            { "  //  abcd", true },
            { "//    abcd", true },
            { "  //  abcd//", true },
            { " /   abcd//", true },
            { "  /  a/bcd//", true },
            { "//  /  abcd", true },
            { "//   / a/b/c/d", true },
            
            { "  /  abcd", false },
            { "/  /  a/bc/d", false },
        };
        for (const auto& test : tests) {
            THEN(test.log()) {
                REQUIRE_NOTHROW(testObject.IsAlreadyCommentedByOneline(test.line_));
                auto result = testObject.IsAlreadyCommentedByOneline(test.line_);
                REQUIRE(result == test.expectedValue_);
            }
        }
    }
}


TEST_CASE("FileParserComments: RemoveOneLine operations", "[RemoveOnelineComments], [RemoveAllOnelineComments]") {
    struct test {
        const std::string line_;
        const std::string expectedValue_;

        std::string log() const {
            return 
                "{ \"" + line_
                + "\" == \"" + expectedValue_
                + "\" }";
        }
    };
    const std::initializer_list<test> tests = {
        {"", ""},
        {"   abcd", "   abcd"},
        {"   // abcd", "   "},
        {"   a//bcd", "   a"},
        {"   abcd//", "   abcd"},
        {"//   abcd", ""},

        {"   /abcd", "   /abcd"},
        {"   /a/b/cd", "   /a/b/cd"},
        {"   abcd/", "   abcd/"},
        {"/   abcd", "/   abcd"},
        {"/   abcd/", "/   abcd/"},

        {" \"  abcd", " \"  abcd"},
        {" \"  abcd\"", " \"  abcd\""},
        {" \"\"  abcd", " \"\"  abcd"},
        {" \'  abcd", " \'  abcd"},
        {" \'  abcd\'", " \'  abcd\'"},
        {" \'\'  abcd", " \'\'  abcd"},

        {" \"\'  abcd", " \"\'  abcd"},
        {" \"\'\"  abcd", " \"\'\"  abcd"},

        {" \"  //abcd", " \"  //abcd"},
        {" \"  abcd\"//", " \"  abcd\""},
        {" \"\"//  abcd", " \"\""},
        {" //\'  abcd", " "},
        {" \'  a/bcd\'", " \'  a/bcd\'"},
        {" \'\'  abc//d", " \'\'  abc"},

        {" \"\'  a//bcd", " \"\'  a//bcd"},
        {" \"\'\"  a//bcd", " \"\'\"  a//bcd"},
        {" \"\'  a/bcd", " \"\'  a/bcd"},
        {" \"\'\"  a/bcd", " \"\'\"  a/bcd"}
    };
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    WHEN("Testing the RemoveOnelineComments()") {
        for (const auto& test : tests) {
            THEN(test.log()) {
                REQUIRE_NOTHROW(testObject.RemoveOnelineComments(test.line_));
                auto result = testObject.RemoveOnelineComments(test.line_);
                REQUIRE(result == test.expectedValue_);
            }
        }
    }
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    WHEN("Testing the RemoveAllOnelineComments()") {
        std::vector<std::string> data; 
        data.reserve(tests.size());
        std::for_each(tests.begin(), tests.end(), [&](auto test){ data.push_back(test.line_); });

        REQUIRE_NOTHROW(testObject.RemoveAllOnelineComments(data));
        auto results = testObject.RemoveAllOnelineComments(data);
        size_t i = 0;
        for (const auto& test : tests) {
            THEN("id: " + std::to_string(i) + "  (" + results.at(i) + ") == (" + test.expectedValue_ + ")") {
                REQUIRE(results.at(i) == test.expectedValue_); 
            }
            ++i;
        }
    }
}


TEST_CASE("FileParserComments: RemoveMultiline operations", "[ClearLine]") {
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    WHEN("Testing the Multiline_ClearLine()") {
        struct test {
            const std::string line_;
            const std::string expectedValue_;
            const bool expectedBool_;

            std::string log() const {
                return 
                    "{ \"" + line_
                    + "\" == \"" + expectedValue_
                    + "\" }";
            }
        };
        const std::initializer_list<test> tests = {
            {"", "", true},
            {"asdfbd", "", true},
        
            {"asdfbd*/", "", false},
            {"asd*/fbd", "fbd", false},
            {"*/asdfbd", "asdfbd", false},
            {"*/asdfbd*/", "asdfbd*/", false},
            {"asd*/fbd*/", "fbd*/", false},
            {"asd*/*/fbd*/", "*/fbd*/", false},
            {"asd/*/fbd*/", "fbd*/", false},
        
            {"asd//fbd*/", "", true},
            {"//asd*/fbd", "", true},
            {"asd//*/fbd*/", "", true},
            {"asd*///fbd*/", "//fbd*/", false},
            {"asd*/f//bd*/", "f//bd*/", false},
            {"a/s/d/*/fbd", "fbd", false},
            {"a/s/d*/fbd", "fbd", false},
        
            {"asd*/fb\"d", "fb\"d", false},
            {"asd*/fb\"\"d", "fb\"\"d", false},
            {"asd*/fb\'d\'", "fb\'d\'", false},
            
            {"a\"sd*/fb\"d", "", true},
            {"a\'sd*/fb\"d", "", true},
            {"a\"s\"d*/fb\"d", "fb\"d", false},
            {"a\'s\'d*/fb\"d", "fb\"d", false},
            {"a\"s\'d*/fb\"d", "", true},
            {"a\'s\"d*/fb\"d", "", true}
        };
        for (const auto& test : tests) {
            THEN(test.log()) {
                bool isCommented = true;
                REQUIRE_NOTHROW(testObject.Multiline_ClearLine(test.line_, isCommented));

                isCommented = true;
                auto result = testObject.Multiline_ClearLine(test.line_, isCommented);
                REQUIRE(result == test.expectedValue_);
                REQUIRE(isCommented == test.expectedBool_);
            }
        }
    }
}




