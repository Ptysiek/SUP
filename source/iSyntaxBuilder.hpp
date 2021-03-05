#pragma once

#include <memory>

#include "DataStructures"


class iSyntaxBuilder {
    using Syntax = DataStructures::Syntax;


public:


    static Syntax buildInstruction(const std::string& syntaxData) {

        
        return std::make_shared<Instruction>(syntaxData);
    }
/*
    Syntaxes BuildProduct() {
        Syntaxes result;

        std::string draft = rawData_;
        size_t i = ClosestSemicolonOrParenthesis(draft);
        
        std::stack<std::shared_ptr<Class>> hierarchy;

        while(i != std::string::npos) {
            std::string syntaxData = draft.substr(0, i + 1);
            syntaxData = RemoveNewLineCharacter(syntaxData);
            draft = draft.substr(i + 1);
            
            if (syntaxData[syntaxData.size() - 1] == ';') {
                if (hierarchy.empty()) {
                    result.emplace_back(std::make_shared<Instruction>(syntaxData));
                }
                else {
                    hierarchy.top()->push_back(std::make_shared<Instruction>(syntaxData));
                }
            }
            else if (syntaxData[syntaxData.size() - 1] == '{') {
                hierarchy.push(std::make_shared<Class>(syntaxData));
            }
            else if (syntaxData[syntaxData.size() - 1] == '}') {
                if (!draft.empty()) {
                    if (draft[0] == ';') {
                        syntaxData += ';';
                        draft = draft.substr(1);
                    }
                }
                
                hierarchy.top()->push_back(std::make_shared<Instruction>(syntaxData));
                
                if (hierarchy.size() < 2) {
                    result.emplace_back(hierarchy.top());
                    if (!hierarchy.empty()) {
                        hierarchy.pop();
                    }
                }
                else {
                    auto oldTop = hierarchy.top();
                    hierarchy.pop();
                    hierarchy.top()->push_back(oldTop);
                }
            }
            i = ClosestSemicolonOrParenthesis(draft);
        }
        return result; 
    }*/
};

