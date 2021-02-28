
#include <iostream>

#include "DataStructures"
//#include "PathInitializer.hpp"
#include "Program.hpp"


int main(int argc, char* argv[]) {
    PathInitializer target(argc, argv);
    Program program(target.getPath());
    program.execute();    

    std::cout << "\n\n";
    return 0;
}



/* TODO:
    - napisz obsługę flag. -md -markdown -txt -text
*/


