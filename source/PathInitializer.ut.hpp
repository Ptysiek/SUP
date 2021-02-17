#pragma once 

#include <string>

#include "PathInitializer.hpp"


class PathInitializer_UnitTest : PathInitializer {
    const std::string testValue_;


public:
    explicit PathInitializer_UnitTest(const std::string& testValue): 
        PathInitializer("",""),
        testValue_(testValue)
    {}

    std::string getTestValue() const { return testValue_; }

    std::string CutoutName() const {
        return PathInitializer::CutoutName(testValue_);
    }

    std::string CutoutFormat() const {
        return PathInitializer::CutoutFormat(testValue_);
    }

    std::string AppendConditionalSlash() const {
        return PathInitializer::AppendConditionalSlash(testValue_);
    }
};




