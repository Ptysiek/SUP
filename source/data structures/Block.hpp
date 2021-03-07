#pragma once

#include <numeric>
#include <string>

#include "iSyntax.hpp"
#include "SyntaxTypes"



class Block : public iSyntax {

protected:
    using iSyntaxes = std::vector<std::shared_ptr<iSyntax>>; 
    using Converter = Tools::Converter;
    const Scope scope_;
    
    
    std::string template_;

    //std::string header_;
    iSyntaxes subElements_;
    iSyntaxes subClasses_;
    iSyntaxes subOperations_;
    iSyntaxes fields_;


public:
    Block(const Scope& scope, const std::string& tem): // const std::string& data): 
        scope_(scope),
        template_(tem),
      //  header_(data),
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
    iSyntaxes GetSyntaxesWithinScope(const Scope scope, const iSyntaxes& source) const {
        iSyntaxes result;
        std::copy_if(source.begin(), source.end(), std::back_inserter(result),
            [scope](auto element){ return (element->getSyntaxScope() == scope); });
        return result;
    }

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

    std::string BuildHeaderName(std::string header, const std::string& key) const {
        if (auto i = header.find('{'); i != std::string::npos) {
            header = header.substr(0, i);
        }
        if (auto i = header.find(key); i != std::string::npos) {
            header = header.substr(i + key.size());
        }
        return Converter::removeWhitespaces(header);
    }

};
