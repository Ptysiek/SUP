#pragma once

#include <numeric>
#include <string>
#include <sstream>

#include "Block.hpp"
#include "iSyntax.hpp"
#include "../Tools"


class Class : public Block {
    using Converter = Tools::Converter;
    std::string className_;

public:
    Class(const std::string& templateData, const std::string& headerData): 
        Block(templateData, headerData),
        className_(BuildClassName(headerData))
    {}
    //enum Type { Instruction, Function, Operation, Class, Structure };
    //enum Memory { Global, Component, Static }; 

    std::string getResult() const override {
        return getResult(0);
    }
    std::string getResult(size_t tabs) const override {
        std::stringstream result;
        const std::string tab = std::string(tabs, '\t');
        
        result << tab << "Class `" << className_ << "` ";
        //result << std::string(tabs, '\t') << header_ << "  " << className_;
        //result << "\n" << std::string(tabs + 1, '\t') + "Has " + std::to_string(CountInstructions()) + " instructions"
        //result << "\n" << std::string(tabs + 1, '\t') + "Has " + std::to_string(CountClasses()) + " classes"
        //result << "\n" << std::string(tabs + 1, '\t') + "Has " + std::to_string(CountBlocks()) + " blocks";
        
        result << "\n\n" << tab << "Class Fields:";
        result << BuildFields(tab + '\t');
        result << "\n\n" << tab << "Class Operations:";
        result << BuildOperations(tab + '\t');

        /*
        if (!subClasses_.empty()) {
            result += "\n\n";
        }
        for (const auto& element : subOperations_) {
            result += '\t' + element->getResult() + "\n";
        }
        for (const auto& element : subClasses_) {
            result += '\t' + element->getResult() + "\n\n";
        }
        */
        return result.str();
    }
    
    Type getSyntaxType() const override { return Type::Class; }
    //Memory getMemoryType() const override { return Memory::  ; } 
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

    std::string BuildFields(const std::string& tab) const {
        std::stringstream result;
        for (const auto& element : fields_) {
            if (element->getResult().find("using") != std::string::npos) {
                continue;
            }
            if (element->getResult().find("};") != std::string::npos) {
                continue;
            }
            result << "\n" << tab << element->getResult();
        }

        return result.str();
    }

    std::string BuildOperations(const std::string& tab) const {
        std::stringstream result;
        for (const auto& element : subOperations_) {
            if (element->getResult().find("using") != std::string::npos) {
                continue;
            }
            if (element->getResult().find("};") != std::string::npos) {
                continue;
            }
            result << "\n" << tab << BuildOperation(element->getResult());
        }

        return result.str();
    }

    std::string BuildOperation(std::string data) const {
        if (auto i = data.find(')'); i != std::string::npos) {
            data = data.substr(0, i + 1);
        }
        //data += "()";
        return Converter::removeWhitespaces(data);
    }


};
