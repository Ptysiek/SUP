#pragma once

#include "../DataStructures"

#include <iostream>
#include <stack>


namespace DataParsers {
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
        
        std::stack<std::shared_ptr<Class>> hierarchy;

        while(i != std::string::npos) {
            std::string syntaxData = draft.substr(0, i + 1);
            syntaxData = RemoveNewLineCharacter(syntaxData);
            draft = draft.substr(i + 1);
            
            if (syntaxData[syntaxData.size() - 1] == ';') {
                if (hierarchy.empty()) {
                    result.emplace_back(std::make_shared<Instruction>(syntaxData));
                }
                else {
                    hierarchy.top()->push_back(std::make_shared<Instruction>(syntaxData));
                }
            }
            else if (syntaxData[syntaxData.size() - 1] == '{') {
                if (hierarchy.empty()) {
                    //result.emplace_back(std::make_shared<Class>(syntaxData));
                    hierarchy.push(std::make_shared<Class>(syntaxData));
                }
            }

            i = ClosestSemicolonOrParenthesis(draft);
        }

        while (!hierarchy.empty()) {
            result.emplace_back(hierarchy.top());
            hierarchy.pop();
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

    std::string RemoveNewLineCharacter( const std::string& line) { 
        if (line.empty()) {
            return line;
        }
        return (line[0] == '\n')? line.substr(1) : line;
    }

};
} // namespace DataParsers




