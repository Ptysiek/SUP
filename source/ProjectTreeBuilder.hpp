#pragma once

#include "ProjectTree.hpp"


class ProjectTreeBuilder {

    ProjectTree product_;

public:
    ProjectTreeBuilder():
        product_()
    {}

    ProjectTree getProduct() const { return product_; }
    



};

