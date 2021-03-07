#pragma once

#include <numeric>
#include <string>

#include "iSyntax.hpp"
#include "SyntaxTypes"



class Block : public iSyntax {
protected:
    const Scope scope_;
    
    
    std::string template_;

    std::string header_;
    std::vector<std::shared_ptr<iSyntax>> subElements_;
    std::vector<std::shared_ptr<iSyntax>> subClasses_;
    std::vector<std::shared_ptr<iSyntax>> subOperations_;
    std::vector<std::shared_ptr<iSyntax>> fields_;

public:
    Block(const Scope& scope, const std::string& tem, const std::string& data): 
        scope_(scope),
        template_(tem),
        header_(data),
        subElements_(),
        subClasses_(),
        subOperations_(),
        fields_()
    {}
    
    void emplace_back(const std::shared_ptr<iSyntax>& subElement) {
        if (subElement->getSyntaxType() == Type::Operation) {
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
    Scope getSyntaxScope() const override { return scope_; }    


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
