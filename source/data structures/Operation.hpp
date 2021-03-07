#pragma once

#include <numeric>
#include <string>

#include "iSyntax.hpp"
#include "Block.hpp"


class Operation : public Block {
    const std::string header_;


public:
    Operation(const Access& access, const std::string& templateData, const std::string& headerData): 
        Block(access, templateData),
        header_(headerData)
    {}
    
    Type getSyntaxType() const override { return Type::Operation; }
    
    std::string getResult(size_t tabs = 0) const override {
        return std::string(tabs, '\t') + header_; 
    }
};


