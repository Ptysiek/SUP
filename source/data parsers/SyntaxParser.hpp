#pragma once

#include "../DataStructures"
#include "../iSyntaxBuilder.hpp"

#include <algorithm>
#include <iostream>
#include <stack>




namespace DataParsers {
class SyntaxParser {
    using Converter = Tools::Converter;
    using Data = DataStructures::Data;
    using Line = DataStructures::Line;
    using Syntaxes = DataStructures::Syntaxes;
    
    struct Workspace {
        Syntaxes result_;
        std::stack<std::shared_ptr<Class>> hierarchy_;
        std::string draft_; 
        std::string syntaxData_; 

        Workspace(const std::string& rawData):
            result_(),
            hierarchy_(),
            draft_(rawData),
            syntaxData_()
        {}
    };

    const std::string rawData_;
    Syntaxes product_;


public:
    SyntaxParser(const Data& data):
        rawData_(MergeRawData(data)),
        product_(BuildProduct())
    {}

    std::string getData() const { return rawData_; }
    Syntaxes getProduct() const { return product_; }


protected:
    //#######################################################################################################
    Syntaxes BuildProduct() {
        Workspace w(rawData_);

        size_t i = ClosestSemicolonOrParenthesis(w.draft_);
        while(i != std::string::npos) {
            w.syntaxData_ = w.draft_.substr(0, i + 1);
            w.syntaxData_ = RemoveNewLineCharacter(w.syntaxData_);
            w.draft_ = w.draft_.substr(i + 1);
            BuildSingleSyntax(w);

            i = ClosestSemicolonOrParenthesis(w.draft_);
        }
        while (!w.hierarchy_.empty()) {
            w.result_.emplace_back(w.hierarchy_.top());
            w.hierarchy_.pop();
        }
        return w.result_; 
    }

    void BuildSingleSyntax(Workspace& w) {
        if (LastCharEquals(';', w.syntaxData_)) {
            AddInstruction(w);
        }
        else if (LastCharEquals('{', w.syntaxData_)) {
            AddBlockOpen(w);
        }
        else if (LastCharEquals('}', w.syntaxData_)) {
            AppendSemicolon(w.syntaxData_, w.draft_);
            AddBlockClose(w);
        }
    }

    //#######################################################################################################
    void AddInstruction(Workspace& w) {
        if (w.hierarchy_.empty()) {
            //w.result_.emplace_back(std::make_shared<Instruction>(w.syntaxData_));
            w.result_.emplace_back(iSyntaxBuilder::buildInstruction(w.syntaxData_));
            return;
        }
        //w.hierarchy_.top()->emplace_back(std::make_shared<Instruction>(w.syntaxData_));
        w.hierarchy_.top()->emplace_back(iSyntaxBuilder::buildInstruction(w.syntaxData_));
    }
    
    void AddBlockOpen(Workspace& w) {
        w.hierarchy_.push(std::make_shared<Class>(w.syntaxData_));
    }
    
    void AddBlockClose(Workspace& w) {
        if (w.hierarchy_.size() == 0) {
            //w.result_.emplace_back(std::make_shared<Instruction>(w.syntaxData_));
            w.result_.emplace_back(iSyntaxBuilder::buildInstruction(w.syntaxData_));
            return;
        }
        //w.hierarchy_.top()->emplace_back(std::make_shared<Instruction>(w.syntaxData_));
        w.hierarchy_.top()->emplace_back(iSyntaxBuilder::buildInstruction(w.syntaxData_));

        if (w.hierarchy_.size() == 1) {
            w.result_.emplace_back(w.hierarchy_.top());
            if (!w.hierarchy_.empty()) {
                w.hierarchy_.pop();
            }
            return;
        }
        auto oldTop = w.hierarchy_.top();
        w.hierarchy_.pop();
        w.hierarchy_.top()->emplace_back(oldTop);
    }

    //#######################################################################################################
    bool LastCharEquals(const char ch, const std::string& str) {  
        return (str[str.size() - 1] == ch); 
    }
    
    size_t ClosestSemicolonOrParenthesis(const Line& line) {
        return std::min(std::min(line.find(';'), line.find('{')), line.find('}'));
    }

    //#######################################################################################################
    std::string MergeRawData(const Data& data) const {
        return Converter::to_string(data);
    }
    
    void AppendSemicolon(std::string& syntaxData, std::string& draft) {
        if (!draft.empty()) {
            if (draft[0] == ';') {
                syntaxData += ';';
                draft = draft.substr(1);
            }
        }
    }
    
    std::string RemoveNewLineCharacter( const std::string& line) { 
        if (line.empty()) {
            return line;
        }
        return (line[0] == '\n')? line.substr(1) : line;
    }

    //#######################################################################################################
};
} // namespace DataParsers




