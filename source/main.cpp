#include <string>
#include <vector>

#include "Program.hpp"

int main() {
    Program program;

    program.ReadConfigurationFiles();
    program.BuildProjectTree();
    program.GenerateDocumentation_TXT();

    return 0;
}
