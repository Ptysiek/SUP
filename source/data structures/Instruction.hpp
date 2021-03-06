#pragma once

#include <string>

#include "iSyntax.hpp"


class Instruction : public iSyntax {

    std::string rawData_;
    
public:
    Instruction(const std::string& data): rawData_(data) {}

    
    std::string getResult(size_t tabs = 0) const override {
        return std::string(tabs, '\t') + rawData_;   
    }
    
    Type getSyntaxType() const override { return Type::Instruction; }
};
