#pragma once

#include <string>

#include "iSyntax.hpp"


class Instruction : public iSyntax {
    const Access access_;    
    const std::string rawData_;
 

public:
    Instruction(const Access access, const std::string& data): 
        access_(access),        
        rawData_(data) 
    {}
    
    Type getSyntaxType() const override { return Type::Instruction; }
    
    Access getSyntaxAccess() const override { return access_; } 
    
    std::string getResult(size_t tabs = 0) const override {
        return std::string(tabs, '\t') + rawData_;   
    }
};


