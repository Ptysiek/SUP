#include <iostream>
#include <string>
#include <vector>

#include "DirectoriesReader.hpp"
#include "DocumentationGenerator.hpp"
#include "IgnoreFileReader.hpp"



int main() {

    //  const std::string startPath = ""; 
    const std::string startPath = "../"; 

    DirectoriesReader dreader;
       
    DocumentationGenerator dgenerator(startPath);

    const auto ignoreDirectories = IgnoreFileReader::getFilesToIgnore();


    auto getstuff = dreader.getDirectories(startPath, ignoreDirectories);
    dgenerator.setDirectoriesVector(getstuff);

    dgenerator.generate();

    return 0;
}
