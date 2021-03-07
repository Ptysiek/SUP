#pragma once

#include <numeric>
#include <string>

#include "iSyntax.hpp"
#include "Block.hpp"


class Operation : public Block {
    
    const std::string header_;


public:
    Operation(const Scope& scope, const std::string& templateData, const std::string& headerData): 
        Block(scope, templateData),
        header_(headerData)// headerData)
    {}
    
    
    std::string getResult(size_t tabs = 0) const override {
        return std::string(tabs, '\t') + header_; 
    }

    Type getSyntaxType() const override { return Type::Operation; }

};
