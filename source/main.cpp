#include <string>
#include <vector>

#include "DocumentationGenerator.hpp"
#include "FileReaders/DefaultFileReader.hpp"
#include "FileReaders/DirectoriesReader.hpp"
#include "FileReaders/IgnoreFileReader.hpp"


int main() {
    const auto startPath = DefaultFileReader::getStartPath(); 
    const auto ignoreDirectories = IgnoreFileReader::getFilesToIgnore();

    DirectoriesReader dirReader;
    auto directories = dirReader.getDirectories(startPath, ignoreDirectories);
       
    DocumentationGenerator documGenerator(startPath);
    documGenerator.setDirectoriesVector(directories);

    documGenerator.generate();
    return 0;
}
