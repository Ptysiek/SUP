#pragma once 

#include <fstream>
#include <string>
#include <vector>



class FileReader {
protected:
    explicit DefaultFileReader() { }


public:
    static std::vector<std::string> ReadFile(const std::string& filename) {
        std::vector<std::string> fileData;
        
        std::ifstream readFile(filename);
        if (!readFile || !readFile.is_open()) {
            return fileData;
        }
        std::string receiver;
        while(std::getline(readFile, receiver)) {
            result.push_back(receiver);
        }
        
        readFile.close();   
        return fileData;
    }
};


