#pragma once

#include <set>

#include "DocumentationGenerator.hpp"
#include "FileReaders/DefaultFileReader.hpp"
#include "FileReaders/DirectoriesReader.hpp"
#include "FileReaders/IgnoreFileReader.hpp"
#include "ProjectTree.hpp"
//#include "ProjectTree_Builder.hpp"


class Program {
    std::string startPath_;
    std::set<std::string> ignoreDirectories_;
    ProjectTree projectTree_;

public:
    explicit Program():
        startPath_(),
        ignoreDirectories_(),
        projectTree_()
    {}

    void ReadConfigurationFiles() {
        startPath_ = DefaultFileReader::getStartPath(); 
        ignoreDirectories_ = IgnoreFileReader::getFilesToIgnore();
    }

    void BuildProjectTree() {
        DirectoriesReader dirReader;
        const auto directories = dirReader.getDirectories(startPath_, ignoreDirectories_);

        projectTree_.setDirectories(directories);
    }

    void GenerateDocumentation_TXT() {
        DocumentationGenerator documGenerator(startPath_, projectTree_);
        documGenerator.generate();
    }
};

