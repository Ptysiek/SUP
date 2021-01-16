
#include "tools/catch.hpp"

#include "DirectoriesReader.ut.hpp"
#include "File.hpp"




//###########################################################################################################
//###########################################################################################################
TEST_CASE("DirectoriesReader: Helper Functions", "[conditionalSlashAppend]") {
    // ______________________________________________________________________________________________________
    // ------------------------------------------------------------------------------------------------------
    WHEN("Testing the conditionalSlashAppend() operation") {
        DirectoriesReader_test testedClass;
        
        struct test {
            const std::string startpath_;
            const std::string result_;

            std::string log() const {
                return 
                    "{ (\"" + startpath_ + 
                    "\") == \"" + result_ +
                    "\" }";
            }
        };
        
        const std::initializer_list<test> tests = {
            {"abcd", "abcd/"},
            {"a", "a/"},
            {"abcd/", "abcd/"},
            {"a/", "a/"},
            {"/", "/"},
            {"ab/cd", "ab/cd/"},
            {"ab/cd/", "ab/cd/"},
            {"/ab/cd", "/ab/cd/"},
            {"/ab/cd/", "/ab/cd/"},
            {"/abcd", "/abcd/"},
            {"/abcd/", "/abcd/"},
            {"/a", "/a/"},
            {"/a/", "/a/"},
            {"//", "//"},
            {"///", "///"},
            {"..", "../"},
            {"../", "../"},
            {".", "./"},
            {"./", "./"}
        };
        for (const auto& test : tests) {
            THEN(test.log()) {
                std::string first_result;
                REQUIRE_NOTHROW(first_result = testedClass.conditionalSlashAppend(test.startpath_));
                
                const auto sec_result = testedClass.conditionalSlashAppend(test.startpath_);
                REQUIRE(first_result == sec_result);
                REQUIRE(first_result == test.result_);
            }
        }
        
        const std::initializer_list<test> bad_tests = {
            {"", ""},
            {"", "/"},
            {"", "abcd"},
            {"", "abcd/"},
            {std::string(), std::string()},
            {std::string(), ""},
            {std::string(), "/"},
            {std::string(), "abcd"},
            {std::string(), "abcd/"}
        };
        for (const auto& test : bad_tests) {
            THEN(test.log()) {
                REQUIRE_THROWS(testedClass.conditionalSlashAppend(test.startpath_));
            }
        }
    }
}


//###########################################################################################################
//###########################################################################################################
TEST_CASE("DirectoriesReader: IgnoreList Functions", "[setIgnoreList], [ignoreListContains]") {
    const std::initializer_list<std::string> set_list_data = {
        "\n",
        "",
        " ",
        ".",
        "..",
        ".git",
        ".gitignore",
        "notes",
        "build",
        "README.md",
        "CMakeLists.txt"
    };

    DirectoriesReader_test testedClass;

    // ______________________________________________________________________________________________________
    // ------------------------------------------------------------------------------------------------------
    WHEN("Testing the setIgnoreList() operation") {
        REQUIRE_NOTHROW(testedClass.setIgnoreList(set_list_data));
        REQUIRE(testedClass.getIgnoreListSize() == set_list_data.size());

        testedClass.setIgnoreList(set_list_data);
        REQUIRE(testedClass.getIgnoreList() == std::set<std::string>(set_list_data));
    }

    // ______________________________________________________________________________________________________
    // ------------------------------------------------------------------------------------------------------
    WHEN("Testing the ignoreListContains() operation") {
        testedClass.setIgnoreList(set_list_data);
        
        for (const auto& directory : set_list_data) {
            REQUIRE_NOTHROW(testedClass.ignoreListContains(directory));
            REQUIRE(testedClass.ignoreListContains(directory) == true);
        }

        for (const auto& directory : set_list_data) {
            for (size_t i = 0; i < 10; ++i) {
                char character = static_cast<char>(i);
                THEN("\"" + directory + "\" + \"" + character + "\" == false") {
                    REQUIRE_NOTHROW(testedClass.ignoreListContains(directory + character));
                    REQUIRE(testedClass.ignoreListContains(directory + character) == false);
                }
            }
        }

        struct test {
            const std::string directory_;
            const bool result_;

            std::string log() const {
                return 
                    "{ (\"" + directory_ + 
                    "\") == \"" + ((result_)? "true" : "false") +
                    "\" }";
            }
        };
        const std::initializer_list<test> tests = {
            {"", true},
            {std::string(), true}
        };
        for (const auto& test : tests) {
            THEN(test.log()) {
                REQUIRE_NOTHROW(testedClass.ignoreListContains(test.directory_));
                REQUIRE(testedClass.ignoreListContains(test.directory_) == test.result_);
            }
        }
    }
}

//###########################################################################################################
//###########################################################################################################
TEST_CASE("DirectoriesReader: MakeFile Functions", "[makeFile], [makeFiles]") {
    struct test {
        const std::string dirName_;
        const std::string startpath_;

        const std::string result_name_;
        const std::string result_path_;
        const std::string result_fullname_;

        std::string log() const {
            return 
                "{ (" + dirName_ + 
                ", " + startpath_ +
                ") == (" + result_name_ +
                ", " + result_path_ +
                ", " + result_fullname_ +
                ") }";
        }
    };
    const std::initializer_list<test> tests = {
        {"abcd", "abcdefg",   "abcd", "dsf", "asdf"}
    };



    // ______________________________________________________________________________________________________
    // ------------------------------------------------------------------------------------------------------
    WHEN("Testing the makeFile() operation") {
    
    }
    WHEN("Testing the makeFiles() operation") {
    
    }
}






