#pragma once

#include <numeric>
#include <string>
#include <sstream>

#include "Block.hpp"
#include "iSyntax.hpp"
#include "../Tools"


class Namespace : public Block {
    using Converter = Tools::Converter;
    std::string header_;

public:
    Namespace(const Scope& scope, const std::string& templateData, const std::string& headerData): 
        Block(scope, templateData, headerData),
        header_(BuildHeaderName(headerData))
    {}

    Type getSyntaxType() const override { return Type::Namespace; }
    
    
    std::string getResult(size_t tabs = 0) const override {
        std::stringstream result;
        const std::string tab = std::string(tabs, '\t');
        
        result << tab << "Namespace `" << header_ << "` {";
        for (const auto& element : fields_) {
            if (element->getResult().find('}') != std::string::npos) {
                continue;
            }
            result << "\n" << element->getResult(tabs + 1); 
        }
        for (const auto& element : subClasses_) {
            result << "\n" << element->getResult(tabs + 1);
        }
        for (const auto& element : subOperations_) {
            result << "\n" << element->getResult(tabs + 1); 
        }
        result << "\n" << tab << "};";
        return result.str();
    }
    

private:
    std::string BuildHeaderName(std::string header) const {
        if (auto i = header.find('{'); i != std::string::npos) {
            header = header.substr(0, i);
        }
        if (auto i = header.find("namespace"); i != std::string::npos) {
            header = header.substr(i + 9);
        }
        return Converter::removeWhitespaces(header);
    }
};
