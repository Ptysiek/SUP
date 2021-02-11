#pragma once

#include <fstream>
#include <string>



class FileIO {
    FileIO() {}

public:
    static void ReadFile(const std::string& path) {
        std::ifstream readFile(path);        
        if (!readFile || !readFile.is_open()) {
            readFile.close();
            throw std::logic_error("Cannot read given file path: " + path + "\n");
        }
        //FileData result;
        //result.emplace_back();
        //PackData* pack = &result.at(result.size()-1); 

        while (true) {
            std::string record;
            if (!std::getline(readFile, record)) {
                break;
            }
            //if (PatternFinder::SequenceBeginning(record, "<core:cityObjectMember>")) {
                //result.emplace_back();
                //pack = &result.at(result.size()-1); 
            //}
            //pack->emplace_back(record);
        }

        readFile.close();
        //return result;
    }

    static void SaveToFile(const std::string& path) {
        std::ofstream output(path);
        
        if (!output || !output.is_open()) {
            throw std::logic_error("Cannot save to file: " + path + "\n");
        }

        output.close();
    }
};




