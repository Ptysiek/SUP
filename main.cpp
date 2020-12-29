#include <iostream>
#include <string>
#include <vector>

#include "DirectoriesReader.hpp"
#include "DocumentationGenerator.hpp"


int main() {

    DirectoriesReader dreader;
    DocumentationGenerator dgenerator;

    auto getstuff = dreader.getDirectories("../");
    dgenerator.setDirectoriesVector(getstuff);

    std::cout << dgenerator.generate();

    return 0;
}
