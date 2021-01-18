#pragma once 

#include <exception>
#include <fstream>
#include <set>
#include <string>



class DefaultFileReader {
protected:
    const static std::string filename_;
    const static std::string defaultStartPath_;
    static std::string programStartPath_;

    explicit DefaultFileReader() { }


public:
    static std::string getStartPath() {
        std::ifstream readFile(filename_);
        
        if (!readFile || !readFile.is_open()) {
            GenerateDefaultFile();
            return defaultStartPath_;
        }
        std::string record;
        std::getline(readFile, record);
        
        readFile.close();   
        programStartPath_ = record;
        return record;
    }


private: 
    static void GenerateDefaultFile() {
        std::ofstream output(filename_);
        if (!output || !output.is_open()) {
            throw std::logic_error("DefaultFileReader::GenerateDefaultFile() Failed to generate");
        }
        output << programStartPath_;
        
        output.close();
    }
};

const std::string DefaultFileReader::filename_ = ".supDefaultPath";
const std::string DefaultFileReader::defaultStartPath_ = "../";
std::string DefaultFileReader::programStartPath_ = defaultStartPath_;


