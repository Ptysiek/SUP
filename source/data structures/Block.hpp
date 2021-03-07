#pragma once

#include <numeric>
#include <string>

#include "iSyntax.hpp"
#include "SyntaxTypes"


class Block : public iSyntax {
protected:
    using SyntaxPtr = std::shared_ptr<iSyntax>;
    using iSyntaxes = std::vector<std::shared_ptr<iSyntax>>; 
    using Converter = Tools::Converter;
    
    const Access access_;
    std::string template_;

    iSyntaxes subClasses_;
    iSyntaxes fields_;
    iSyntaxes operations_;
    iSyntaxes elements_;


public:
    Block(const Access& access, const std::string& tem): 
        access_(access),
        template_(tem),
        subClasses_(),
        fields_(),
        operations_(),
        elements_()
    {}
    
    Type getSyntaxType() const override { return Type::Block; }
    
    Access getSyntaxAccess() const override { return access_; }    
    
    void emplace_back(const SyntaxPtr& subElement) {
        if (subElement->getSyntaxType() == Type::Class) {
            subClasses_.emplace_back(subElement);
            return;
        }
        if (subElement->getSyntaxType() == Type::Operation) {
            operations_.emplace_back(subElement);
            return;
        }
        if (subElement->getSyntaxType() == Type::Instruction) {
            fields_.emplace_back(subElement);
            return;
        }
        elements_.emplace_back(subElement);
    }


protected:
    iSyntaxes GetSyntaxesWithinAccess(const Access access, const iSyntaxes& source) const {
        iSyntaxes result;
        std::copy_if(source.begin(), source.end(), std::back_inserter(result),
            [access](auto element){ return (element->getSyntaxAccess() == access); });
        return result;
    }
    
    std::string BuildHeaderName(std::string header, const std::string& key) const {
        if (auto i = header.find('{'); i != std::string::npos) {
            header = header.substr(0, i);
        }
        if (auto i = header.find(key); i != std::string::npos) {
            header = header.substr(i + key.size());
        }
        return Converter::removeWhitespaces(header);
    }
};


