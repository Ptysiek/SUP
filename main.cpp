#include <iostream>
#include <string>
#include <vector>

#include "DirectoriesReader.hpp"



int main() {

    DirectoriesReader dr;

    auto getstuff = dr.getDirectories("../");
    
    for (const auto& record : getstuff) {
        std::cout << record << "\n";
    }

    return 0;
}
