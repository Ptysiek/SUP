#include <iostream>
#include <string>
#include <vector>

#include "DirectoriesReader.hpp"
#include "DocumentationGenerator.hpp"


int main() {

    const std::string startPath = "../"; 

    DirectoriesReader dreader;
    DocumentationGenerator dgenerator(startPath);

    auto getstuff = dreader.getDirectories(startPath);
    dgenerator.setDirectoriesVector(getstuff);

    dgenerator.generate();

    return 0;
}
