#pragma once

#include <string>
#include <sstream>

#include "Block.hpp"
#include "iSyntax.hpp"
#include "../Tools"
#include "SyntaxTypes"


class ClassStruct : public Block {
    using Converter = Tools::Converter;
    using Access = SyntaxTypes::Access;
    using SyntaxData = std::vector<std::string>;
    
    const std::string typeName_;
    const std::string headerName_;


public:
    ClassStruct(const Access& access, const std::string& templateData, const std::string& headerData): 
        Block(access, templateData), 
        typeName_((access == Access::Public)? "struct" : "class"),
        headerName_(BuildHeaderName(headerData, typeName_))
    {}
    
    Type getSyntaxType() const override { return Type::Class; }

    std::string getResult(size_t tabs = 0) const override {
        std::stringstream result;
        const std::string tab = std::string(tabs, '\t');
        
        result << tab << typeName_ << " `" << headerName_ << "` {";
        result << EnlistFields(tab);
        result << EnlistOperations(tab);
        result << EnlistSubClasses(tabs);

        result << "\n" << tab << "};";
        return result.str();
    }
 

private:
    std::string EnlistSubClasses(const size_t tabs) const {
        std::stringstream result;
        for (const auto& element : Block::subClasses_) {
            result << "\n\n" << element->getResult(tabs + 1);
        }
        return result.str();
    }
    
    std::string EnlistFields(const std::string& tab) const {
        std::stringstream result;
        result << BuildEnlistedData(Access::Private, Block::fields_, tab, typeName_ + " private fields:");
        result << BuildEnlistedData(Access::Protected, Block::fields_, tab, typeName_ + " protected fields:");
        result << BuildEnlistedData(Access::Public, Block::fields_, tab, typeName_ + " public fields:");
        return result.str();
    }

    std::string EnlistOperations(const std::string& tab) const {
        std::stringstream result;
        result << BuildEnlistedData(Access::Public, Block::operations_, tab, typeName_ + " public operations:");
        result << BuildEnlistedData(Access::Protected, Block::operations_, tab, typeName_ + " protected operations:");
        result << BuildEnlistedData(Access::Private, Block::operations_, tab, typeName_ + " private operations:");
        return result.str();
    }

    std::string BuildEnlistedData(
            const Access access, 
            const iSyntaxes& syntaxes, 
            const std::string& tab,
            const std::string& title) const 
    {
        std::stringstream result;
        auto group = Block::GetSyntaxesWithinAccess(access, syntaxes); 
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



