
#include <iostream>

#include "Program.hpp"
#include "ProgramInitializer.hpp"


int main(int argc, char* argv[]) {
    ProgramInitializer target(argc, argv);
    Program program(target);
    program.execute();    

    std::cout << "\n\n";
    return 0;
}



/* TODO:
    - napisz obsługę flag. -md -markdown -txt -text

    - flag supprot
*/


