#pragma once

#include <numeric>
#include <string>

#include "iSyntax.hpp"


class Block : public iSyntax {

protected:
    std::string template_;

    std::string header_;
    std::vector<std::shared_ptr<iSyntax>> subElements_;
    std::vector<std::shared_ptr<iSyntax>> subClasses_;
    std::vector<std::shared_ptr<iSyntax>> subOperations_;
    std::vector<std::shared_ptr<iSyntax>> fields_;

public:
    Block(const std::string& tem, const std::string& data): 
        template_(tem),
        header_(data),
        subElements_(),
        subClasses_(),
        subOperations_(),
        fields_()
    {}
    //enum Type { Instruction, Function, Operation, Class, Structure };
    //enum Memory { Global, Component, Static }; 
    std::string getResult() const override {
        return getResult(0);
    }
    std::string getResult(size_t tabs) const override {
        std::string result = std::string(tabs, '\t') + header_ 
            + "\n" + std::string(tabs + 1, '\t') + "Has " + std::to_string(CountInstructions()) + " instructions"
            + "\n" + std::string(tabs + 1, '\t') + "Has " + std::to_string(CountClasses()) + " classes"
            + "\n" + std::string(tabs + 1, '\t') + "Has " + std::to_string(CountBlocks()) + " blocks";
        
        /*
        if (!subClasses_.empty()) {
            result += "\n\n";
        }
        for (const auto& element : subOperations_) {
            result += '\t' + element->getResult() + "\n";
        }
        for (const auto& element : subClasses_) {
            result += '\t' + element->getResult() + "\n\n";
        }
        */
        return result;
    }
    
    void emplace_back(const std::shared_ptr<iSyntax>& subElement) {
        if (subElement->getSyntaxType() == Type::Block) {
            subOperations_.emplace_back(subElement);
            return;
        }
        if (subElement->getSyntaxType() == Type::Class) {
            subClasses_.emplace_back(subElement);
            return;
        }
        if (subElement->getSyntaxType() == Type::Instruction) {
            fields_.emplace_back(subElement);
            return;
        }
        subElements_.emplace_back(subElement);
    }

    Type getSyntaxType() const override { return Type::Block; }
    //Memory getMemoryType() const override { return Memory::  ; } 
protected:

    size_t CountInstructions() const {
        return std::accumulate(subElements_.begin(), subElements_.end(), 0, 
            [](int sum, auto e){ return (e->getSyntaxType() == Type::Instruction)? sum + 1 : sum; });
    }
    
    size_t CountBlocks() const {
        return std::accumulate(subElements_.begin(), subElements_.end(), 0, 
            [](int sum, auto e){ return (e->getSyntaxType() == Type::Block)? sum + 1 : sum; });
    }
    
    size_t CountClasses() const {
        return subClasses_.size();
    }


};
