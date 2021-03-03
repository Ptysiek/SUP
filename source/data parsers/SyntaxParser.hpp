#pragma once

#include "../DataStructures"

#include <iostream>

class SyntaxParser {
    using Converter = Tools::Converter;
    using Data = DataStructures::Data;
    using Line = DataStructures::Line;
    using Syntax = DataStructures::Syntax;
    
    std::string rawData_;
    Syntax product_;

public:
    SyntaxParser(const Data& data):
        rawData_(MergeRawData(data)),
        product_(BuildProduct())
    {}

    std::string getData() const { return rawData_; }
    Syntax getProduct() const { return product_; }

protected:
    std::string MergeRawData(const Data& data) const {
        return Converter::to_string(data);
    }

    Syntax BuildProduct() {
        Syntax result;

        std::string draft = rawData_;
        size_t i = ClosestSemicolonOrParenthesis(draft);
        
        while(i != std::string::npos) {
            
            std::string syntaxData = draft.substr(0, i + 1);
            syntaxData = ClearFromNewLine(syntaxData);
            //std::cout << i << std::endl;
            draft = draft.substr(i + 1);
            
            
            result.emplace_back(std::make_shared<Instruction>(syntaxData));
            i = ClosestSemicolonOrParenthesis(draft);
        }

        return result; 
    }

    size_t ClosestSemicolonOrParenthesis(const Line& line) {
        return std::min(line.find(';'), line.find('{'));
    }
    

    bool hasCoolon(const Line& line) {
        return (line.find(';') == std::string::npos);
    }

    bool hasO_Bracket(const Line& line) {
        return (line.find('{') == std::string::npos);
    }
    
    bool hasC_Bracket(const Line& line) {
        return (line.find('}') == std::string::npos);
    }

    std::string ClearFromNewLine(const std::string& line) {
        return (line[0] == '\n')? line.substr(1) : line;
    }

};




