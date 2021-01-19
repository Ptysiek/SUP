#include <string>
#include <vector>

#include "DocumentationGenerator.hpp"
#include "FileReaders/DefaultFileReader.hpp"
#include "FileReaders/DirectoriesReader.hpp"
#include "FileReaders/IgnoreFileReader.hpp"
#include "ProjectTree.hpp"



int main() {
    const auto startPath = DefaultFileReader::getStartPath(); 
    const auto ignoreDirectories = IgnoreFileReader::getFilesToIgnore();
    ProjectTree projTree;

    DirectoriesReader dirReader;
    auto directories = dirReader.getDirectories(startPath, ignoreDirectories);
       
    projTree.setDirectories(directories);


    DocumentationGenerator documGenerator(startPath);
    documGenerator.setProjectTree(projTree);

    documGenerator.generate();
    return 0;
}
