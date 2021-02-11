#pragma once

#

#include "FileIO.hpp"
#include "PathInitializer.hpp"

//#include "DataParser.hpp"
//#include "Repairer.hpp"
//#include "DataStructures.hpp"

class Program {

    const PathInitializer& targetPath_;


public:
    explicit Program(const PathInitializer& target):
        targetPath_(target)
    {}

    void execute() {


    }

private:

};

