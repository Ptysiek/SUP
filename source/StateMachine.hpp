#pragma once

#include <memory>
#include <stack>
#include <string>
#include <vector>


struct Node {
    const std::string originFile_;
    const std::string name_;
    const std::string fullName_;
    //std::string type_;
    std::vector<std::shared_ptr<Node>> nodes_;
    
    explicit Node(
            const std::string& originFile, 
            const std::string& name,
            const std::string& fullName):
        originFile_(originFile),
        name_(name),
        fullName_(fullName),
        nodes_()
    {}
};


class StateMachine {

    std::vector<Node> collectiveData_;

    
    size_t index_;
    std::string processedFileData_;
    bool is_multilineComment_;
    std::vector<std::string> connectedDirs_;


public:
    explicit StateMachine():
        collectiveData_(),
        index_(),
        processedFileData_(),
        is_multilineComment_(),
        connectedDirs_()
    { }

    std::string Process(const std::map<std::string,std::string> allFilesData) {
        std::string result = "";
        for (const auto& [fileName, fileData] : allFilesData) {
            result += "\n\n";
            result += ProcessNewFile(fileName, fileData);
            result += "------------------------\n";
            for (const auto& record : connectedDirs_) {
                result += record + "\n";
            }
            result += "------------------------\n";
            result += "\n\n";
        }
        return result;
    }


private:
    void initMachine(std::string fileData) {
        index_ = 0;
        processedFileData_ = fileData;
        is_multilineComment_ = false;
        connectedDirs_.clear();
    }

    std::string ProcessNewFile(const std::string& fileName, const std::string& fileData) {
        initMachine(fileData);
        
        std::string result = "";
        std::string fullNameEntry = "";

        Node test (fileName, "class", fullNameEntry + "class");

        while (index_ < processedFileData_.size()) {
            std::string oneLine = ReadOneLine();
        
            oneLine = StripFromComments(oneLine);
            oneLine = StripFromExtraWhiteSpaces(oneLine);
            oneLine = StripFromDirectives(oneLine);


            
            if (oneLine != "" && oneLine != "\n") {
                result += oneLine + '\n';
            }
        }

        for (const auto& character : fileData) {
            if (character != ' ') {

            }
        }
        return result;
    }
    
    std::string ReadOneLine() {
        std::string result = "";
        for ( ; index_ < processedFileData_.size(); ++index_) {
            const char character = processedFileData_[index_];
            if (character == '\n') {
                ++index_;
                return result;
            }
            result += character;
        }
        return result;
    }
    
    std::string StripFromDirectives(const std::string& oneLine) {

        if (oneLine[0] != '#') {
            return oneLine;
        }
        size_t k = 0;
        const std::string code = "include";

        size_t i = 1;
        for ( ; i < oneLine.size() && k < code.size(); ++i) {
            if (oneLine[i] != code[k] && oneLine[i] != ' ') {
                return "";
            }
            else if (oneLine[i] == code[k]) {
                ++k;
            }
        }
        ++i;
        for ( ; i < oneLine.size(); ++i) {
            if (oneLine[i] != '"' && oneLine[i] != '\"' && oneLine[i] != '<' && oneLine[i] != ' ') {
                return "";
            }
        }
        std::string directory = "sup";
        for ( ; i < oneLine.size(); ++i) {
            if (oneLine[i] == '"' && oneLine[i] == '\"' && oneLine[i] == '>') {
                break;
            }
            directory += oneLine[i];
        }
        connectedDirs_.push_back(directory);
        return "";
    }

    std::string StripFromExtraWhiteSpaces(const std::string& oneLine) {
        std::string result = "";

        size_t i = 0;
        for ( ; i < oneLine.size(); ++i) {
            if (oneLine[i] != ' ' && oneLine[i] != '\n' && oneLine[i] != '\t') {
                break;
            }
        }

        for ( ; i < oneLine.size(); ++i) {
            result += oneLine[i];
        }

        return result;
    }


    std::string StripFromComments(const std::string& oneLine) {
        std::string result = "";
        bool lastCharacter = true;

        size_t i = 1;
        while (i < oneLine.size()) {
            if (is_multilineComment_) {
                if (oneLine[i-1] == '*' && oneLine[i] == '/') {
                    is_multilineComment_ = false;
                    lastCharacter = false;
                }
            }
            else {
                if (oneLine[i-1] == '/' && oneLine[i] == '/') {
                    return result;
                }
                if (oneLine[i-1] == '/' && oneLine[i] == '*') {
                    is_multilineComment_ = true;
                    ++i;
                    continue;
                }
                lastCharacter = true;
                result += oneLine[i-1];
            }
            ++i;
        }
        if (!is_multilineComment_ && lastCharacter && i == oneLine.size()) {
            result += oneLine[i-1];
        }
        return result;
    }
};

