#pragma once

#include "FileIO.hpp"
#include "ProjectTree.hpp"

#include <string>


class ProjectTreeBuilder {
    const std::string initPath_;
    ProjectTree product_;

public: 
    explicit ProjectTreeBuilder(const std::string& initPath): 
        initPath_(initPath),
        product_(BuildProduct())
    {}

    ProjectTree getProduct() {
        return product_;
    }

private:
    ProjectTree BuildProduct() {

        return ProjectTree();
    }




};

