
#include <iostream>

#include "PathInitializer.hpp"
#include "Program.hpp"


int main(int argc, char* argv[]) {
    PathInitializer target(argc, argv);
    Program program(target.getPath());
    program.execute();    

    std::cout << "\n\n";
    return 0;
}



/* TODO:
    - file.hpp
    przerobić na klasę. Napisz getery do rzeczy

    - IgnoreFiles.hpp
    napisz set niezmiennych ignorów
    napisz set domyślnych ignorów
    zrób obsługę plików
    IgnoreFiles jest polem klasy FileIO

    - otestuj wszystko

    - napisz obsługę flag. -md -markdown -txt -text
*/


