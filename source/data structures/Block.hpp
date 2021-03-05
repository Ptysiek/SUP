#pragma once

#include <numeric>
#include <string>

#include "iSyntax.hpp"


class Block : public iSyntax {

    std::string template_;

    std::string header_;
    std::vector<std::shared_ptr<iSyntax>> subElements_;

    std::vector<std::shared_ptr<iSyntax>> subClasses_;

public:
    Block(const std::string& tem, const std::string& data): 
        template_(tem),
        header_(data),
        subElements_(),
        subClasses_()
    {}
    //enum Type { Instruction, Function, Operation, Class, Structure };
    //enum Memory { Global, Component, Static }; 

    std::string getResult() const override {
        std::string result = header_ 
            + "\nHas " + std::to_string(CountInstructions()) + " instructions"
            + "\nHas " + std::to_string(CountClasses()) + " classes";
        
        result += "\n\n";
        for (const auto& element : subClasses_) {
            result += '\t' + element->getResult() + "\n\n";
        }
        
        return result;
    }
    
    void emplace_back(const std::shared_ptr<iSyntax>& subElement) {
        if (subElement->getSyntaxType() == Type::Class) {
            subClasses_.emplace_back(subElement);
            return;
        }
        subElements_.emplace_back(subElement);
    }

    Type getSyntaxType() const override { return Type::Block; }
    //Memory getMemoryType() const override { return Memory::  ; } 
private:

    size_t CountInstructions() const {
        return std::accumulate(subElements_.begin(), subElements_.end(), 0, 
            [](int sum, auto e){ return (e->getSyntaxType() == Type::Instruction)? sum + 1 : sum; });
    }
    
    size_t CountClasses() const {
        return subClasses_.size();
    }


};
