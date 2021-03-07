#pragma once

#include <numeric>
#include <string>
#include <sstream>

#include "Block.hpp"
#include "iSyntax.hpp"
#include "../Tools"


class Class : public Block {
    using Converter = Tools::Converter;
    using Scope = SyntaxTypes::Scope;
    
    std::string className_;

public:
    Class(const Scope& scope, const std::string& templateData, const std::string& headerData): 
        Block(scope, templateData, headerData),
        className_(BuildHeaderName(headerData, "class"))
    {}

    std::string getResult(size_t tabs = 0) const override {
        std::stringstream result;
        const std::string tab = std::string(tabs, '\t');
        
        result << tab << "Class `" << className_ << "` {";
        
        result << "\n" << tab << '\t' << "Class Private Fields:";
        result << BuildFields(tab + "\t\t", SyntaxTypes::Scope::Private);
        result << "\n" << tab << '\t' << "Class Protected Fields:";
        result << BuildFields(tab + "\t\t", SyntaxTypes::Scope::Protected);
        result << "\n" << tab << '\t' << "Class Public Fields:";
        result << BuildFields(tab + "\t\t", SyntaxTypes::Scope::Public);

        result << "\n\n" << tab << '\t' << "Class Public Operations:";
        result << BuildOperations(tab + "\t\t", SyntaxTypes::Scope::Public);
        result << "\n" << tab << '\t' << "Class Protected Operations:";
        result << BuildOperations(tab + "\t\t", SyntaxTypes::Scope::Protected);
        result << "\n" << tab << '\t' << "Class Private Operations:";
        result << BuildOperations(tab + "\t\t", SyntaxTypes::Scope::Private);

        result << "\n" << tab << "};";
        return result.str();
    }
    
    Type getSyntaxType() const override { return Type::Class; }


private:
    std::string BuildClassName(std::string header) const {
        if (auto i = header.find('{'); i != std::string::npos) {
            header = header.substr(0, i);
        }
        if (auto i = header.find("class"); i != std::string::npos) {
            header = header.substr(i + 5);
        }
        return Converter::removeWhitespaces(header);
    }

    std::string BuildFields(const std::string& tab, const Scope scope) const {
        std::stringstream result;
        size_t count = 0;
        for (const auto& element : GetSyntaxesWithinScope(scope, fields_)) {
            std::string data = RemoveScope(element->getResult());
            if (data.find("using") != std::string::npos) {
                continue;
            }
            if (data.find("};") != std::string::npos) {
                continue;
            }
            data = Converter::removeWhitespaces(data);
            result << "\n" << tab << ++count << "] " << data;
        }
        if (count == 0) {
            result << "\n" << tab << "This class has no Fields within that AccessSpecifier";
        }
        return result.str();
    }
    
    std::string BuildOperations(const std::string& tab, const Scope scope) const {
        std::stringstream result;
        size_t count = 0;
        for (const auto& element : GetSyntaxesWithinScope(scope, subOperations_)) {
            if (element->getSyntaxScope() == scope) {
                result << "\n" << tab << ++count << "] " << BuildOperation(element->getResult());
            }
        }
        if (count == 0) {
            result << "\n" << tab << "This class has no Operations within that AccessSpecifier";
        }
        return result.str();
    }

    std::string BuildOperation(std::string data) const {
        data = RemoveScope(data);
        if (auto i = data.find(')'); i != std::string::npos) {
            data = data.substr(0, i + 1);
        }
        return Converter::removeWhitespaces(data);
    }

    std::string RemoveScope(std::string data) const {
        if (auto i = data.find("public:"); i != std::string::npos) {
            data = data.substr(i + 7);
        }
        if (auto i = data.find("private:"); i != std::string::npos) {
            data = data.substr(i + 8);
        }
        if (auto i = data.find("protected:"); i != std::string::npos) {
            data = data.substr(i + 10);
        }
        return data;
    }

};
