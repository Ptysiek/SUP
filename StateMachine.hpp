#pragma once

#include <memory>
#include <stack>
#include <string>
#include <vector>


struct Node {
    const std::string name_;
    const std::string fullName_;
    std::string type_;

    std::vector<std::shared_ptr<Node>> nodes_;
};


class StateMachine {

    std::vector<Node> collectiveData;


public:

    void Process(std::map<std::string,std::string> allFilesData) {
        for (const auto& [fileName, fileData] : allFilesData) {
            ProcessNewFile(fileName, fileData);
        }
    }


private:
    void initMachine() {
        

    }

    void ProcessNewFile(const std::string& fileName, const std::string& fileData) {
        initMachine();
    
        for (const auto& 
    
    
    }
};

