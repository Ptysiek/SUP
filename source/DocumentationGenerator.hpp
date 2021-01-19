#pragma once

#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>

#include "File.hpp"
#include "StateMachine.hpp"
#include "EntriesBuilder.hpp"


class DocumentationGenerator {
    const std::string startPath_;
    const std::string filename_;

    ProjectTree projTree_;



public:
    explicit DocumentationGenerator(const std::string& startPath, const ProjectTree& projTree):
        startPath_(startPath),
        filename_("sup.txt"),
        projTree_(projTree)
    {}

    bool generate() {
        std::string data = "";

        data += EntriesBuilder::getHeader();
        data += "File generation date: " + EntriesBuilder::getDate();

        data += "\n\n";
        data += EntriesBuilder::getTableOfContents(projTree_);

        const auto& dirs = projTree_.getDirectoriesPaths();

        std::map<std::string,std::string> allFilesData;
        for (const auto& file : dirs) {
            auto fileData_tmp = readFromFile(startPath_ + file);
            allFilesData[file] = fileData_tmp; 
            //data += fileData_tmp;
            //data += "\n\n";
        }
        StateMachine sm;
        data += sm.Process(allFilesData);

        std::ofstream output(filename_);
        if (!output || !output.is_open()) {
            return false;
        }
        output << data;

        output.close();
        return true;
    }

private:



    std::string readFromFile(const std::string& path) {
        //std::vector<std::string> fileData;
        //fileData.reserve(500);
        std::string fileData = "";

        std::ifstream readFile(path);
        std::string tmp;
        while (std::getline(readFile, tmp)) {
            if (tmp == "\n" || tmp == "") {
                continue;
            }
            fileData += tmp;
            fileData += "\n";
        }
        /*
        while (readFile) {
            std::string tmp;
            readFile >> tmp;
            //fileData.push_back(tmp);
            fileData += tmp;
            fileData += ' ';
        }
        //*/
        readFile.close();
        
        return fileData;
    }




    
};

