#pragma once

#include <numeric>
#include <string>
#include <sstream>

#include "Block.hpp"
#include "iSyntax.hpp"
#include "../Tools"


class Namespace : public Block {
    const std::string header_;


public:
    Namespace(const Access& access, const std::string& templateData, const std::string& headerData): 
        Block(access, templateData), 
        header_(BuildHeaderName(headerData, "namespace"))
    {}

    Type getSyntaxType() const override { return Type::Namespace; }
    
    std::string getResult(size_t tabs = 0) const override {
        std::stringstream result;
        const std::string tab = std::string(tabs, '\t');
        
        result << tab << "Namespace `" << header_ << "` {";
        for (const auto& element : Block::fields_) {
            if (element->getResult().find('}') != std::string::npos) {
                continue;
            }
            result << "\n" << element->getResult(tabs + 1); 
        }
        for (const auto& element : Block::subClasses_) {
            result << "\n" << element->getResult(tabs + 1);
        }
        for (const auto& element : Block::operations_) {
            result << "\n" << element->getResult(tabs + 1); 
        }
        result << "\n" << tab << "};";
        return result.str();
    }
};
