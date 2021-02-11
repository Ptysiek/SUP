
#include <iostream>

#include "PathInitializer.hpp"
#include "Program.hpp"


int main(int argc, char* argv[]) {
    PathInitializer target(argc, argv);
    Program program(target);
    program.execute();    

    std::cout << "\n\n";
    return 0;
}






