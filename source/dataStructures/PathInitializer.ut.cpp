#include "../plugins/catch.hpp"
#include "PathInitializer.ut.hpp"


TEST_CASE("PathInitializer: static operations", "[CutoutName], [CutoutFormat], [AppendConditionalSlash]") {
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    WHEN("Testing the CutoutName()") {
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
            { PathInitializer_UnitTest("\n"), "\n" },
            { PathInitializer_UnitTest(""), "" },
            { PathInitializer_UnitTest("."), "." },
            { PathInitializer_UnitTest(".."), ".." },
            { PathInitializer_UnitTest("./"), "./" },
            { PathInitializer_UnitTest("../"), "../" },
            
            { PathInitializer_UnitTest("a."), "a" },
            { PathInitializer_UnitTest("a.abcd"), "a" },
            { PathInitializer_UnitTest("abcd."), "abcd" },
            { PathInitializer_UnitTest("abcd.abcd"), "abcd" },

            { PathInitializer_UnitTest(".a."), ".a" },
            { PathInitializer_UnitTest(".a.abcd"), ".a" },
            { PathInitializer_UnitTest(".abcd."), ".abcd" },
            { PathInitializer_UnitTest(".abcd.abcd"), ".abcd" },
    
            { PathInitializer_UnitTest("..a."), "." },
            { PathInitializer_UnitTest("..a.abcd"), "." },
            { PathInitializer_UnitTest("..abcd."), "." },
            { PathInitializer_UnitTest("..abcd.abcd"), "." }
        };

        for (const auto& test : tests) {
            THEN(test.log()) {
                REQUIRE_NOTHROW(test.object_.CutoutName());
                auto result = test.object_.CutoutName();
                REQUIRE(result == test.expectedValue_);
            }
        }
    }
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    WHEN("Testing the CutoutFormat()") {
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
            { PathInitializer_UnitTest("\n"), "" },
            { PathInitializer_UnitTest(""), "" },
            { PathInitializer_UnitTest("."), "" },
            { PathInitializer_UnitTest(".."), "" },
            { PathInitializer_UnitTest("./"), "" },
            { PathInitializer_UnitTest("../"), "" },
            
            { PathInitializer_UnitTest("a."), "." },
            { PathInitializer_UnitTest("a.abcd"), ".abcd" },
            { PathInitializer_UnitTest("abcd."), "." },
            { PathInitializer_UnitTest("abcd.abcd"), ".abcd" },

            { PathInitializer_UnitTest(".a."), "." },
            { PathInitializer_UnitTest(".a.abcd"), ".abcd" },
            { PathInitializer_UnitTest(".abcd."), "." },
            { PathInitializer_UnitTest(".abcd.abcd"), ".abcd" },
    
            { PathInitializer_UnitTest("..a."), ".a." },
            { PathInitializer_UnitTest("..a.abcd"), ".a.abcd" },
            { PathInitializer_UnitTest("..abcd."), ".abcd." },
            { PathInitializer_UnitTest("..abcd.abcd"), ".abcd.abcd" }
        };

        for (const auto& test : tests) {
            THEN(test.log()) {
                REQUIRE_NOTHROW(test.object_.CutoutFormat());
                auto result = test.object_.CutoutFormat();
                REQUIRE(result == test.expectedValue_);
            }
        }
    }
    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    WHEN("Testing the AppendConditionalSlash()") {
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
            { PathInitializer_UnitTest("\n"), "\n/" },
            { PathInitializer_UnitTest(""), "" },
            { PathInitializer_UnitTest("."), "./" },
            { PathInitializer_UnitTest(".."), "../" },
            { PathInitializer_UnitTest("./"), "./" },
            { PathInitializer_UnitTest("../"), "../" },
            
            { PathInitializer_UnitTest("a."), "a./" },
            { PathInitializer_UnitTest("a.abcd"), "a.abcd/" },
            { PathInitializer_UnitTest(".abcd."), ".abcd./" },
            { PathInitializer_UnitTest("..abcd.abcd"), "..abcd.abcd/" },

            { PathInitializer_UnitTest("a./"), "a./" },
            { PathInitializer_UnitTest("a.abcd/"), "a.abcd/" },
            { PathInitializer_UnitTest(".abcd./"), ".abcd./" },
            { PathInitializer_UnitTest("..abcd.abcd/"), "..abcd.abcd/" },

            { PathInitializer_UnitTest("a.//"), "a.//" },
            { PathInitializer_UnitTest("a.abcd//"), "a.abcd//" },
            { PathInitializer_UnitTest(".abcd.//"), ".abcd.//" },
            { PathInitializer_UnitTest("..abcd.abcd//"), "..abcd.abcd//" }
        };

        for (const auto& test : tests) {
            THEN(test.log()) {
                REQUIRE_NOTHROW(test.object_.AppendConditionalSlash());
                auto result = test.object_.AppendConditionalSlash();
                REQUIRE(result == test.expectedValue_);
            }
        }
    }
}




