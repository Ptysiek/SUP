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

    for (const auto& record : getstuff) {
        std::cout << record << "\n";
    }

    return 0;
}
