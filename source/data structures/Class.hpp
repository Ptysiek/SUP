#pragma once

#include <string>
#include <sstream>

#include "Block.hpp"
#include "iSyntax.hpp"
#include "../Tools"


class Class : public Block {
    using Converter = Tools::Converter;
    using Scope = SyntaxTypes::Scope;
    using SyntaxData = std::vector<std::string>;
    
    std::string className_;


public:
    Class(const Scope& scope, const std::string& templateData, const std::string& headerData): 
        Block(scope, templateData, headerData),
        className_(BuildHeaderName(headerData, "class"))
    {}
    
    Type getSyntaxType() const override { return Type::Class; }

    std::string getResult(size_t tabs = 0) const override {
        std::stringstream result;
        const std::string tab = std::string(tabs, '\t');
        
        result << tab << "Class `" << className_ << "` {";
        result << EnlistFields(tab);
        result << EnlistOperations(tab);

        result << "\n" << tab << "};";
        return result.str();
    }
 

private:
    std::string EnlistFields(const std::string& tab) const {
        std::stringstream result;
        result << BuildEnlistedData(Scope::Private, fields_, tab, "Class Private Fields:");
        result << BuildEnlistedData(Scope::Protected, fields_, tab, "Class Protected Fields:");
        result << BuildEnlistedData(Scope::Public, fields_, tab, "Class Public Fields:");
        return result.str();
    }

    std::string EnlistOperations(const std::string& tab) const {
        std::stringstream result;
        result << BuildEnlistedData(Scope::Public, subOperations_, tab, "Class Public Operations:");
        result << BuildEnlistedData(Scope::Protected, subOperations_, tab, "Class Protected Operations:");
        result << BuildEnlistedData(Scope::Private, subOperations_, tab, "Class Private Operations:");
        return result.str();
    }

    std::string BuildEnlistedData(
            const Scope scope, 
            const iSyntaxes& syntaxes, 
            const std::string& tab,
            const std::string& title) const 
    {
        std::stringstream result;
        auto group = Block::GetSyntaxesWithinScope(scope, syntaxes); 
        auto data = ClearSyntaxData(group);
        if (!data.empty()) {
            result << "\n\n" << tab << '\t' << title;
            result << EnlistSyntaxes(data,  tab + "\t\t"); 
        }
        return result.str();
    }

    SyntaxData ClearSyntaxData(const iSyntaxes& syntaxes) const {
        SyntaxData result;
        for (const auto& element : syntaxes) {
            std::string data = element->getResult();
            if (data.find("};") != std::string::npos) {
                continue;
            }
            data = Converter::removeWhitespaces(data);
            data = BuildOperation(data);
            result.emplace_back(data);
        }
        return result;
    }
    
    std::string EnlistSyntaxes(const SyntaxData& syntaxes, const std::string& tab) const {
        std::stringstream result;
        for (size_t i = 0; i < syntaxes.size(); ++i) {
            result << "\n" << tab << (i + 1) << "] " << syntaxes[i];
        }
        return result.str();
    }

    std::string BuildOperation(std::string data) const {
        if (auto i = data.find(')'); i != std::string::npos) {
            data = data.substr(0, i + 1);
        }
        return Converter::removeWhitespaces(data);
    }
};



