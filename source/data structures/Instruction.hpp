#pragma once

#include <string>

#include "iSyntax.hpp"


class Instruction : public iSyntax {
    const Scope scope_;    
    std::string rawData_;
    
public:
    Instruction(const Scope scope, const std::string& data): 
        scope_(scope),        
        rawData_(data) 
    {}

    
    std::string getResult(size_t tabs = 0) const override {
        return std::string(tabs, '\t') + rawData_;   
    }
    
    Type getSyntaxType() const override { return Type::Instruction; }
    Scope getSyntaxScope() const override { return scope_; } 
};
