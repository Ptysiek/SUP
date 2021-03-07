#pragma once

#include "../DataStructures"

#include <algorithm>
#include <iostream>
#include <stack>


namespace DataParsers {
class SyntaxParser {
    using Converter = Tools::Converter;
    using Data = DataStructures::Data;
    using Line = DataStructures::Line;
    using Syntaxes = DataStructures::Syntaxes;
 
    using Syntax = DataStructures::Syntax;
    using BlockSyntax = DataStructures::BlockSyntax;
    
    using Scope = SyntaxTypes::Scope;

    struct Workspace {
        Syntaxes result_;
        std::stack<std::shared_ptr<Block>> hierarchy_;
        std::string draft_; 
        std::string syntaxData_; 

        Workspace(const std::string& rawData):
            result_(),
            hierarchy_(),
            draft_(rawData),
            syntaxData_()
        {}
    };

    SyntaxTypes::Scope currentScope_;
    const std::string rawData_;
    Syntaxes product_;


public:
    SyntaxParser(const Data& data):
        currentScope_(SyntaxTypes::Scope::None),
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
            if (auto scope = IndicateCurrentScope(w); scope != Scope::None) {
                currentScope_ = scope; 
            }
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
            w.result_.emplace_back(buildInstruction(w.syntaxData_));
            return;
        }
        w.hierarchy_.top()->emplace_back(buildInstruction(w.syntaxData_));
    }
    
    void AddBlockOpen(Workspace& w) {
        w.hierarchy_.push(buildBlock(w.syntaxData_));
    }
    
    void AddBlockClose(Workspace& w) {
        if (w.hierarchy_.size() == 0) {
            w.result_.emplace_back(buildInstruction(w.syntaxData_));
            return;
        }
        w.hierarchy_.top()->emplace_back(buildInstruction(w.syntaxData_));

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
    
    SyntaxTypes::Scope IndicateCurrentScope(Workspace& w) {
        if (auto i = w.syntaxData_.find("public:"); i != std::string::npos) {
            w.syntaxData_ = w.syntaxData_.substr(i + 7);
            w.syntaxData_ = RemoveNewLineCharacter(w.syntaxData_);
            return SyntaxTypes::Scope::Public;
        }
        if (auto i = w.syntaxData_.find("private:"); i != std::string::npos) {
            w.syntaxData_ = w.syntaxData_.substr(i + 8);
            w.syntaxData_ = RemoveNewLineCharacter(w.syntaxData_);
            return SyntaxTypes::Scope::Private;
        }
        if (auto i = w.syntaxData_.find("protected:"); i != std::string::npos) {
            w.syntaxData_ = w.syntaxData_.substr(i + 10);
            w.syntaxData_ = RemoveNewLineCharacter(w.syntaxData_);
            return SyntaxTypes::Scope::Protected;
        }
        return SyntaxTypes::Scope::None;
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
    BlockSyntax buildBlock(std::string syntaxData) {
        auto temp = CutOutTemplate(syntaxData);      

        if (auto i = syntaxData.find("namespace"); i != std::string::npos) {
            return std::make_shared<Namespace>(currentScope_, temp, syntaxData);
        }
        if (syntaxData.find("class") != std::string::npos) {
            currentScope_ = SyntaxTypes::Scope::Private;
            return std::make_shared<Class>(currentScope_, temp, syntaxData);
        }
        if (syntaxData.find("struct") != std::string::npos) {
            currentScope_ = SyntaxTypes::Scope::Public;
            //return std::make_shared<Struct>(temp, syntaxData);
        }
        if (syntaxData.find("(") != std::string::npos) {
            //return BuildOperation(syntaxData); 
        }

        return std::make_shared<Operation>(currentScope_, temp, syntaxData);
    }

    Syntax buildInstruction(const std::string& syntaxData) {
        return std::make_shared<Instruction>(currentScope_, syntaxData);
    }


private:
    static std::string CutOutTemplate(std::string& syntaxData) {
        auto begin = syntaxData.find("template");
        if (begin == std::string::npos) {
            return std::string();
        }
        auto end =  syntaxData.find(">", begin);
        if (end == std::string::npos) {
            return std::string();
        }
        std::string result = syntaxData.substr(begin, end - begin);
        std::string tmp = syntaxData.substr(end + 1);
        syntaxData = syntaxData.substr(0, begin) + " " + tmp; 
        Converter::removeWhitespaces(result);
        Converter::removeWhitespaces(syntaxData);
        return result;
    }
};
} // namespace DataParsers


