#include <string>
#include <vector>

#include "DefaultFileReader.hpp"
#include "DirectoriesReader.hpp"
#include "DocumentationGenerator.hpp"
#include "IgnoreFileReader.hpp"


int main() {

    const auto startPath = DefaultFileReader::getStartPath(); 
    const auto ignoreDirectories = IgnoreFileReader::getFilesToIgnore();

    DirectoriesReader dreader;
       
    DocumentationGenerator dgenerator(startPath);



    auto directories = dreader.getDirectories(startPath, ignoreDirectories);
    dgenerator.setDirectoriesVector(directories);

    dgenerator.generate();

    return 0;
}
